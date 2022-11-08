#pragma once

#include "GameFramework/PlayerController.h"
#include "SRPlayerController.generated.h"

class UHUDWidget;
class USRGamePlayWidget;
class USRCheckRankWidget;
class USRRankingWidget;
class ASRPlayerState;

UCLASS()
class SHOOTING_RANGE_API ASRPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASRPlayerController();
	
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override;
	void ChangeInputMode(bool bGameMode = true);

	ASRPlayerState* GetPlayerState() { return SRPlayerState; };

	UFUNCTION(BlueprintCallable)
	void AddGameScore(int EarnedScore);

	void SubtractCurrentBullet();

	void OnGameEnd();

	void ShowRankingWidget();

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

private:
	void OnGamePause();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<UHUDWidget> HUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<UUserWidget> HuddyWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<USRGamePlayWidget> MenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<USRCheckRankWidget> CheckRankWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<USRRankingWidget> RankingWidgetClass;

private:
	UPROPERTY()
	ASRPlayerState* SRPlayerState;
	 
	UPROPERTY()
	UHUDWidget* HUDWidget;

	UPROPERTY()
	UUserWidget* HuddyWidget;

	UPROPERTY()
	USRGamePlayWidget* MenuWidget;

	UPROPERTY()
	USRCheckRankWidget* CheckRankWidget;

	UPROPERTY()
	USRRankingWidget* RankingWidget;

	FInputModeGameOnly GameInputMode;
	FInputModeUIOnly UIInputMode;
};