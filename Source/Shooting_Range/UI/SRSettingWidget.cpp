#include "SRSettingWidget.h"
#include "SRSaveGame.h"
#include "Kismet/GameplayStatics.h"

void USRSettingWidget::UpdateSaveData()
{
	USRSaveGame* SaveGame = Cast<USRSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Save1"), 0));
	if (nullptr == SaveGame)
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