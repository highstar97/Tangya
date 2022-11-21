#include "SRPlayerController.h"
#include "SRCharacter.h"
#include "Shooting_RangeGameModeBase.h"
#include "SRPlayerState.h"
#include "SRSaveGame.h"
#include "HUDWidget.h"
#include "SRGamePlayWidget.h"
#include "SRCheckRankWidget.h"
#include "SRRankingWidget.h"
#include "SRSelectWeaponWidget.h"
#include "SRSettingWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

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
		MenuWidgetClass = UI_PAUSE_C.Class;
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

void ASRPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	UE_LOG(LogTemp, Warning, TEXT("Player Controller PostInitializeComponents"));
}

void ASRPlayerController::OnPossess(APawn* aPawn)
{
	UE_LOG(LogTemp, Warning, TEXT("Player Controller OnPossess"));
	Super::OnPossess(aPawn);
}

void ASRPlayerController::ChangeInputMode(bool bGameMode)
{
	if (bGameMode)
	{
		SetInputMode(GameInputMode);
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(UIInputMode);
		bShowMouseCursor = true;
	}
}

void ASRPlayerController::AddGameScore(int32 EarnedScore)
{
	int32 BonusScore = 0;
	switch (Cast<ASRCharacter>(GetCharacter())->Weapon->GetWeaponAbilityScore())
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
	SRPlayerState->AddGameScore(EarnedScore + BonusScore);
}

void ASRPlayerController::SubtractCurrentBullet()
{
	SRPlayerState->SetCurrentBullets(SRPlayerState->GetCurrentBullets() - 1);
}

void ASRPlayerController::AddTotalBullet(EWeaponAbilityBullet WeaponAbilityBullet)
{
	int32 BonusBullet = 0;
	switch (WeaponAbilityBullet)
	{
	case(EWeaponAbilityBullet::NONE):
	{
		BonusBullet = 0;
		break;
	}
	case(EWeaponAbilityBullet::ADD3):
	{
		BonusBullet = 3;
		break;
	}
	case(EWeaponAbilityBullet::SUBTRACT3):
	{
		BonusBullet = -3;
		break;
	}
	default:
	{
		BonusBullet = 0;
		break;
	}
	}
	SRPlayerState->SetTotalBullets(SRPlayerState->GetTotalBullets() + BonusBullet);
	SRPlayerState->SetCurrentBullets(SRPlayerState->GetTotalBullets());
}

void ASRPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ChangeInputMode(true);

	PlayerCameraManager->ViewPitchMin = -45.0f;
	PlayerCameraManager->ViewPitchMax = 45.0f;

	HUDWidget = CreateWidget<UHUDWidget>(this, HUDWidgetClass);
	HuddyWidget = CreateWidget<UUserWidget>(this, HuddyWidgetClass);
	SettingWidget = CreateWidget<USRSettingWidget>(this, SettingWidgetClass);

	SRPlayerState = Cast<ASRPlayerState>(PlayerState);
	if (nullptr != SRPlayerState)
	{
		SRPlayerState->BindPlayerController(this);
		HUDWidget->BindPlayerState(SRPlayerState);
		SRPlayerState->SetTotalBullets(Cast<AShooting_RangeGameModeBase>(GetWorld()->GetAuthGameMode())->GetTotalBullets());
		SRPlayerState->SetCurrentBullets(SRPlayerState->GetTotalBullets());
		SRPlayerState->OnPlayerStateChanged.Broadcast();
	}
}

void ASRPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("GamePause"), EInputEvent::IE_Pressed, this, &ASRPlayerController::OnGamePause);
}

void ASRPlayerController::OnGamePause()
{
	MenuWidget = CreateWidget<USRGamePlayWidget>(this, MenuWidgetClass);
	ensure(nullptr != MenuWidget);
	MenuWidget->AddToViewport(3);

	SetPause(true);
	ChangeInputMode(false);
}

void ASRPlayerController::OnGameEnd()
{
	CheckRankWidget = CreateWidget<USRCheckRankWidget>(this, CheckRankWidgetClass);
	ensure(nullptr != CheckRankWidget);
	CheckRankWidget->AddToViewport();
	FTimerHandle WaitHandle;
	float WaitTime = 1.0f;
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
		{

			CheckRankWidget->UpdateWidget();

		}), WaitTime, false);

	//SetPause(true);
	ChangeInputMode(false);
}

void ASRPlayerController::TurnOnHUDWidget()
{
	ensure(nullptr != HUDWidget);
	HUDWidget->AddToViewport();
}

void ASRPlayerController::TurnOffHUDWidget()
{
	ensure(nullptr != HUDWidget);
	HUDWidget->RemoveFromParent();
}

void ASRPlayerController::TurnOnHuddyWidget()
{
	ensure(nullptr != HuddyWidget);
	HuddyWidget->AddToViewport();
}

void ASRPlayerController::TurnOffHuddyWidget()
{
	ensure(nullptr != HuddyWidget);
	HuddyWidget->RemoveFromParent();
}

void ASRPlayerController::TurnOnRankingWidget()
{
	RankingWidget = CreateWidget<USRRankingWidget>(this, RankingWidgetClass);
	ensure(nullptr != RankingWidget);
	RankingWidget->AddToViewport();
	RankingWidget->UpdateWidget();

	SetPause(true);
	ChangeInputMode(false);
}

void ASRPlayerController::TurnOnSelectWeaponWidget()
{
	SelectWeaponWidget = CreateWidget<USRSelectWeaponWidget>(this, SelectWeaponWidgetClass);
	ensure(nullptr != SelectWeaponWidget);
	SelectWeaponWidget->AddToViewport();
	SelectWeaponWidget->UpdateWidget();

	SetPause(true);
	ChangeInputMode(false);
}

void ASRPlayerController::TurnOffSelectWeaponWidget()
{
	ensure(nullptr != SelectWeaponWidget);
	SelectWeaponWidget->RemoveFromParent();

	SetPause(false);
	ChangeInputMode(true);
}

void ASRPlayerController::TurnOnSettingWidget()
{
	if (!SettingWidget)
	{
		SettingWidget = CreateWidget<USRSettingWidget>(this, SettingWidgetClass);
	}
	ensure(nullptr != SettingWidget);
	USRSaveGame* SaveGame = Cast<USRSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Save1"), 0));
	if (nullptr == SaveGame)
	{
		SaveGame = GetMutableDefault<USRSaveGame>();
	}

	SettingWidget->UpdateSettingData(SaveGame);

	SettingWidget->AddToViewport();
}