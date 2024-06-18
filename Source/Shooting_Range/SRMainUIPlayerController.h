#pragma once

#include "GameFramework/PlayerController.h"
#include "SRMainUIPlayerController.generated.h"

class UUserWidget;

UCLASS()
class SHOOTING_RANGE_API ASRMainUIPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASRMainUIPlayerController();

protected:
	virtual void BeginPlay() override;

private:
	void ToggleMainWidget(bool bIsNeedToTurnOn);

private:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> MainWidgetClass;

	UPROPERTY()
	UUserWidget* MainWidget;
};
