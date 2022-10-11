#pragma once

#include "GameFramework/PlayerController.h"
#include "SRPlayerController.generated.h"

UCLASS()
class SHOOTING_RANGE_API ASRPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASRPlayerController();

	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<UUserWidget> HuddyWidgetClass;

private:
	UPROPERTY()
	UUserWidget* HuddyWidget;
};