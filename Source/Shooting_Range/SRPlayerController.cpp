#include "SRPlayerController.h"

#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

#include "SRCharacter.h"
#include "SRBaseGameMode.h"
#include "SRPlayerState.h"
#include "SRSaveGame.h"
#include "HUDWidget.h"
#include "SRGamePlayWidget.h"
#include "SRCheckRankWidget.h"
#include "SRRankingWidget.h"
#include "SRSelectWeaponWidget.h"
#include "SRSettingWidget.h"

ASRPlayerController::ASRPlayerController()
{
	static ConstructorHelpers::FClassFinder<UHUDWidget> UI_HUD_C(TEXT("/Game/UI/UI_HUD.UI_HUD_C"));
	if (UI_HUD_C.Succeeded())
	{
		HUDWidgetClass = UI_HUD_C.Class;
	}
	
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUDDY_C(TEXT("/Game/Blueprints/Huddy_BP.Huddy_BP_C"));
	if (UI_HUDDY_C.Succeeded())
	{
		HuddyWidgetClass = UI_HUDDY_C.Class;
	}

	static ConstructorHelpers::FClassFinder<USRGamePlayWidget> UI_PAUSE_C(TEXT("/Game/UI/UI_Pause.UI_Pause_C"));
	if (UI_PAUSE_C.Succeeded())
	{
		PauseWidgetClass = UI_PAUSE_C.Class;
	}
	
	static ConstructorHelpers::FClassFinder<USRCheckRankWidget> UI_CHECKRANK_C(TEXT("/Game/UI/UI_CheckRank.UI_CheckRank_C"));
	if (UI_CHECKRANK_C.Succeeded())
	{
		CheckRankWidgetClass = UI_CHECKRANK_C.Class;
	}

	static ConstructorHelpers::FClassFinder<USRRankingWidget> UI_RANKING_C(TEXT("/Game/UI/UI_RANKING.UI_RANKING_C"));
	if (UI_RANKING_C.Succeeded())
	{
		RankingWidgetClass = UI_RANKING_C.Class;
	}

	static ConstructorHelpers::FClassFinder<USRSelectWeaponWidget> UI_SELECTWEAPON_C(TEXT("/Game/UI/UI_SelectWeapon.UI_SelectWeapon_C"));
	if (UI_SELECTWEAPON_C.Succeeded())
	{
		SelectWeaponWidgetClass = UI_SELECTWEAPON_C.Class;
	}

	static ConstructorHelpers::FClassFinder<USRSettingWidget> UI_SETTING_C(TEXT("/Game/UI/UI_Settings.UI_Settings_C"));
	if (UI_SETTING_C.Succeeded())
	{
		SettingWidgetClass = UI_SETTING_C.Class;
	}
}

void ASRPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PlayerCameraManager->ViewPitchMin = -45.0f;
	PlayerCameraManager->ViewPitchMax = 45.0f;

	// Just create widgets and open it when needed
	HUDWidget = CreateWidget<UHUDWidget>(this, HUDWidgetClass);
	HuddyWidget = CreateWidget<UUserWidget>(this, HuddyWidgetClass);
	PauseWidget = CreateWidget<USRGamePlayWidget>(this, PauseWidgetClass);
	CheckRankWidget = CreateWidget<USRCheckRankWidget>(this, CheckRankWidgetClass);
	RankingWidget = CreateWidget<USRRankingWidget>(this, RankingWidgetClass);
	SelectWeaponWidget = CreateWidget<USRSelectWeaponWidget>(this, SelectWeaponWidgetClass);
	SettingWidget = CreateWidget<USRSettingWidget>(this, SettingWidgetClass);

	ChangeInputMode(EInputMode::GAMEONLY);
}

void ASRPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("GamePause"), EInputEvent::IE_Pressed, this, &ASRPlayerController::OnGamePause);
}

void ASRPlayerController::ToggleWidget(bool bIsNeedToTurnOn, TSubclassOf<UUserWidget> Widget)
{
	if (!ensure(Widget != nullptr)) return;

	if (Cast<USRSelectWeaponWidget>(Widget) != nullptr)
	{
		ToggleSelectWeaponWidget(bIsNeedToTurnOn);
	}
	else
	{
		UUserWidget* UserWidget = Cast<UUserWidget>(Widget);
		if (!ensure(UserWidget != nullptr)) return;

		bIsNeedToTurnOn == true ? UserWidget->AddToViewport() : UserWidget->RemoveFromParent();
	}
}

void ASRPlayerController::ToggleHUDWidget(bool bIsNeedToTurnOn)
{
	if (!ensure(HUDWidget != nullptr)) return;

	bIsNeedToTurnOn == true ? HUDWidget->AddToViewport() : HUDWidget->RemoveFromParent();
}

void ASRPlayerController::ToggleHuddyWidget(bool bIsNeedToTurnOn)
{
	if (!ensure(HuddyWidget != nullptr)) return;

	bIsNeedToTurnOn == true ? HuddyWidget->AddToViewport() : HuddyWidget->RemoveFromParent();
}

void ASRPlayerController::TogglePauseWidget(bool bIsNeedToTurnOn)
{
	if (!ensure(PauseWidget != nullptr)) return;

	bIsNeedToTurnOn == true ? PauseWidget->AddToViewport() : PauseWidget->RemoveFromParent();
}

void ASRPlayerController::ToggleCheckRankWidget(bool bIsNeedToTurnOn)
{
	if (!ensure(CheckRankWidget != nullptr)) return;

	bIsNeedToTurnOn == true ? CheckRankWidget->AddToViewport() : CheckRankWidget->RemoveFromParent();
}

void ASRPlayerController::ToggleRankingWidget(bool bIsNeedToTurnOn)
{
	if (!ensure(RankingWidget != nullptr)) return;

	bIsNeedToTurnOn == true ? RankingWidget->AddToViewport() : RankingWidget->RemoveFromParent();
}

void ASRPlayerController::ToggleSelectWeaponWidget(bool bIsNeedToTurnOn)
{
	if (!ensure(SelectWeaponWidget != nullptr)) return;

	if (bIsNeedToTurnOn)
	{
		SelectWeaponWidget->AddToViewport();
		SelectWeaponWidget->UpdateWidget();
		SetPause(true);
		ChangeInputMode(EInputMode::UIONLY);
	}
	else
	{
		SelectWeaponWidget->RemoveFromParent();

		SetPause(false);
		ChangeInputMode(EInputMode::GAMEONLY);
	}
}

void ASRPlayerController::ToggleSettingWidget(bool bIsNeedToTurnOn)
{
	if (!ensure(SettingWidget != nullptr)) return;

	bIsNeedToTurnOn == true ? SettingWidget->AddToViewport() : SettingWidget->RemoveFromParent();

	// TODO : Make Function
	USRSaveGame* SaveGame = Cast<USRSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Save1"), 0));
	if (nullptr == SaveGame)
	{
		SaveGame = GetMutableDefault<USRSaveGame>();
	}

	SettingWidget->UpdateSettingData(SaveGame);
}

void ASRPlayerController::OnGameEnd()
{
	ToggleCheckRankWidget(true);

	FTimerHandle WaitHandle;
	float WaitTime = 1.0f;	// Widget is updated after WaitTime(1.0 sec) so that the last bullet's score can be Added.
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{
			CheckRankWidget->UpdateWidget();
		}), WaitTime, false);

	ChangeInputMode(EInputMode::UIONLY);
}

void ASRPlayerController::EarnScore(const float EarnedScore)
{
	float BonusScore = 0;

	switch (Cast<ASRCharacter>(GetCharacter())->GetCurrentWeapon()->GetWeaponAbilityScore())
	{
	case(EWeaponAbilityScore::NONE):
	{
		BonusScore = 0;
		break;
	}
	case(EWeaponAbilityScore::ADD1):
	{
		BonusScore = 1;
		break;
	}
	case(EWeaponAbilityScore::ADD2):
	{
		BonusScore = 2;
		break;
	}
	default:
	{
		BonusScore = 0;
		break;
	}
	}

	ASRPlayerState* SRPlayerState = GetPlayerState<ASRPlayerState>();
	if (!ensure(SRPlayerState != nullptr)) return;

	SRPlayerState->AddScore(EarnedScore + BonusScore);
}

void ASRPlayerController::RegisterRanking()
{
	if (!ensure(RankingWidget != nullptr)) return;

	ToggleRankingWidget(true);
	RankingWidget->UpdateWidget();
	SetPause(true);
	ChangeInputMode(EInputMode::UIONLY);
}

void ASRPlayerController::ConsumeBullets(const int32 NumOfConsumption)
{
	if (Cast<ASRBaseGameMode>(GetWorld()->GetAuthGameMode())->GetCurrentMode() != EGameMode::Competition) return;

	ASRPlayerState* SRPlayerState = GetPlayerState<ASRPlayerState>();
	if (!ensure(SRPlayerState != nullptr)) return;

	SRPlayerState->SetNumOfCurrentBullets(SRPlayerState->GetNumOfCurrentBullets() - NumOfConsumption);
}

void ASRPlayerController::AddBonusBulletsByAbility(EWeaponAbilityBullet WeaponAbilityBullet)
{
	int32 BonusBullets = 0;
	switch (WeaponAbilityBullet)
	{
	case(EWeaponAbilityBullet::NONE):
	{
		BonusBullets = 0;
		break;
	}
	case(EWeaponAbilityBullet::ADD3):
	{
		BonusBullets = 3;
		break;
	}
	case(EWeaponAbilityBullet::SUBTRACT3):
	{
		BonusBullets = -3;
		break;
	}
	default:
	{
		BonusBullets = 0;
		break;
	}
	}

	ASRPlayerState* SRPlayerState = GetPlayerState<ASRPlayerState>();
	if (!ensure(SRPlayerState != nullptr)) return;

	SRPlayerState->SetNumOfTotalBullets(SRPlayerState->GetNumOfTotalBullets() + BonusBullets);
	SRPlayerState->SetNumOfCurrentBullets(SRPlayerState->GetNumOfTotalBullets());
}

void ASRPlayerController::ChangeInputMode(EInputMode InputMode)
{
	switch (InputMode)
	{
	case EInputMode::BASE:
		break;
	case EInputMode::GAMEANDUI:
		break;
	case EInputMode::GAMEONLY:
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
		break;
	}
	case EInputMode::UIONLY:
	{
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
		break;
	}
	}
}

float ASRPlayerController::GetGauge() const
{
	if (HUDWidget)
	{
		return HUDWidget->GetCurrentGauge();
	}

	return -1.0f;
}

void ASRPlayerController::ChangebGauging(bool NewBoolean)
{
	if (HUDWidget)
	{
		HUDWidget->SetbIsGauging(NewBoolean);
	}
}

void ASRPlayerController::ChangeGauge(float NewGauge)
{
	if (HUDWidget)
	{
		HUDWidget->SetCurrentGauge(NewGauge);
		HUDWidget->UpdateTimingCatcher();
	}
}

void ASRPlayerController::OnGamePause()
{
	if (PauseWidget->IsInViewport())
	{
		TogglePauseWidget(false);
		SetPause(false);
		ChangeInputMode(EInputMode::GAMEONLY);
	}
	else
	{
		TogglePauseWidget(true);
		SetPause(true);
		ChangeInputMode(EInputMode::UIONLY);
	}
}