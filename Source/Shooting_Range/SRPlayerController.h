#pragma once

#include "GameFramework/PlayerController.h"
#include "SRPlayerController.generated.h"

UCLASS()
class SHOOTING_RANGE_API ASRPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ASRPlayerController();
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override;
	void ChangeInputMode(bool bGameMode = true);

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class USRGamePlayWidget> MenuWidgetClass;

private:
	void OnGamePause();

	UPROPERTY()
	class USRGamePlayWidget* MenuWidget;

	FInputModeGameOnly GameInputMode;
	FInputModeUIOnly UIInputMode;
};
