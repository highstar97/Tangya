#pragma once

#include "Blueprint/UserWidget.h"
#include "SRSettingWidget.generated.h"

class USRSaveGame;

UCLASS()
class SHOOTING_RANGE_API USRSettingWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void UpdateSaveData();

	void UpdateSettingData(USRSaveGame* SaveGame);

public:
	UPROPERTY(BlueprintReadWrite, Category = Setting)
	float Sound;

	UPROPERTY(BlueprintReadWrite, Category = Setting)
	float Light;

	UPROPERTY(BlueprintReadWrite, Category = Setting)
	float MouseSensitivity;
};
