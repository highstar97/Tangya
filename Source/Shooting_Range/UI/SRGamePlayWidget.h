#pragma once

#include "Blueprint/UserWidget.h"
#include "SRGamePlayWidget.generated.h"

class UButton;

UCLASS()
class SHOOTING_RANGE_API USRGamePlayWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnResumeClicked();

	UFUNCTION()
	void OnReturnToTitleClicked();

	UFUNCTION()
	void OnSettingClicked();

private:
	UPROPERTY(meta = (BindWidget))
	UButton* Button_Resume;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_ReturnToTitle;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_Setting;
};