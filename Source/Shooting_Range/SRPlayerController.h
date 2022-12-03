#pragma once

#include "GameFramework/PlayerController.h"
#include "SRWeapon.h"
#include "SRPlayerController.generated.h"

class UHUDWidget;
class USRGamePlayWidget;
class USRCheckRankWidget;
class USRRankingWidget;
class USRSelectWeaponWidget;
class USRSettingWidget;
class ASRPlayerState;

UCLASS()
class SHOOTING_RANGE_API ASRPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASRPlayerController();
	
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override;

	UFUNCTION(BlueprintCallable)
	void ChangeInputMode(bool bGameMode = true);

	ASRPlayerState* GetPlayerState() { return SRPlayerState; };
	float GetGauge();

	UFUNCTION(BlueprintCallable)
	void AddGameScore(int32 EarnedScore);

	void SubtractCurrentBullet();

	void AddTotalBullet(EWeaponAbilityBullet WeaponAbilityBullet);

	void OnGameEnd();

	void TurnOnHUDWidget();
	void TurnOffHUDWidget();

	void TurnOnHuddyWidget();
	void TurnOffHuddyWidget();

	void TurnOnRankingWidget();

	UFUNCTION(BlueprintCallable)
	void TurnOnSelectWeaponWidget();
	void TurnOffSelectWeaponWidget();

	UFUNCTION(BlueprintCallable)
	void TurnOnSettingWidget();

	void ChangebGauging(bool NewBoolean);

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<USRSelectWeaponWidget> SelectWeaponWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<USRSettingWidget> SettingWidgetClass;

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

	UPROPERTY()
	USRSelectWeaponWidget* SelectWeaponWidget;

	UPROPERTY()
	USRSettingWidget* SettingWidget;

	FInputModeGameOnly GameInputMode;
	FInputModeUIOnly UIInputMode;
};