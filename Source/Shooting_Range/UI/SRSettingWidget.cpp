#include "SRSettingWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

#include "SRSaveGame.h"
#include "SRPlayerController.h"

void USRSettingWidget::UpdateSaveData()
{
	USRSaveGame* SaveGame = Cast<USRSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Save1"), 0));
	if (SaveGame == nullptr)
	{
		SaveGame = GetMutableDefault<USRSaveGame>();
	}

	SaveGame->UpdateSettingData(Sound, Light, MouseSensitivity);
	if (!UGameplayStatics::SaveGameToSlot(SaveGame, TEXT("Save1"), 0))
	{
		UE_LOG(LogTemp, Error, TEXT("SaveGame Error!"));
	}
}

void USRSettingWidget::UpdateSettingData(USRSaveGame* SaveGame)
{
	Sound = SaveGame->GetSettingData().Sound;
	Light = SaveGame->GetSettingData().Light;
	MouseSensitivity = SaveGame->GetSettingData().MouseSensitivity;
}

void USRSettingWidget::OnExitClicked()
{
	ASRPlayerController* SRPlayerController = GetOwningPlayer<ASRPlayerController>();
	if (!ensure(SRPlayerController != nullptr)) return;

	SRPlayerController->ToggleSettingWidget(false);
	SRPlayerController->ChangeInputMode(EInputMode::GAMEONLY);
	SRPlayerController->SetPause(false);
}

void USRSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (!ensure(Button_Exit != nullptr)) return;
	Button_Exit->OnClicked.AddDynamic(this, &USRSettingWidget::OnExitClicked);
}