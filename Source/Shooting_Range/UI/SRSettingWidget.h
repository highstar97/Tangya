#pragma once

#include "Blueprint/UserWidget.h"
#include "SRSettingWidget.generated.h"

class USRSaveGame;
class UButton;

UCLASS()
class SHOOTING_RANGE_API USRSettingWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void UpdateSaveData();

	void UpdateSettingData(USRSaveGame* SaveGame);

	UFUNCTION()
	void OnExitClicked();

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(BlueprintReadWrite, Category = Setting)
	float Sound;

	UPROPERTY(BlueprintReadWrite, Category = Setting)
	float Light;

	UPROPERTY(BlueprintReadWrite, Category = Setting)
	float MouseSensitivity;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Exit;
};
