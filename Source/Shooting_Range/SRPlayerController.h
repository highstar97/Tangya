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

UENUM(BlueprintType)
enum class EInputMode : uint8
{
	BASE,
	GAMEANDUI,
	GAMEONLY,
	UIONLY
};

UCLASS()
class SHOOTING_RANGE_API ASRPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASRPlayerController();

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

public:
	void ToggleWidget(bool bIsNeedToTurnOn, TSubclassOf<UUserWidget> Widget);

	void ToggleHUDWidget(bool bIsNeedToTurnOn);

	void ToggleHuddyWidget(bool bIsNeedToTurnOn);

	void TogglePauseWidget(bool bIsNeedToTurnOn);

	void ToggleCheckRankWidget(bool bIsNeedToTurnOn);

	void ToggleRankingWidget(bool bIsNeedToTurnOn);

	UFUNCTION(BlueprintCallable)
	void ToggleSelectWeaponWidget(bool bIsNeedToTurnOn);

	void ToggleSettingWidget(bool bIsNeedToTurnOn);

public:
	void OnGameEnd();
	
	UFUNCTION(BlueprintCallable)
	void EarnScore(const float EarnedScore);

	void RegisterRanking();

	void ConsumeBullets(const int32 NumOfConsumption);

	void AddBonusBulletsByAbility(EWeaponAbilityBullet WeaponAbilityBullet);

	UFUNCTION(BlueprintCallable)
	void ChangeInputMode(EInputMode InputMode);

	float GetGauge() const;
	void ChangebGauging(bool NewBoolean);
	void ChangeGauge(float NewGauge);

private:
	void OnGamePause();

private:
	UPROPERTY(EditDefaultsOnly, Category = "UI.HUD")
	TSubclassOf<UHUDWidget> HUDWidgetClass;

	UPROPERTY(VisibleInstanceOnly, Category = "UI.HUD")
	UHUDWidget* HUDWidget;

	UPROPERTY(EditInstanceOnly, Category = "UI.Huddy")
	TSubclassOf<UUserWidget> HuddyWidgetClass;

	UPROPERTY(VisibleInstanceOnly, Category = "UI.Huddy")
	UUserWidget* HuddyWidget;

	UPROPERTY(EditDefaultsOnly, Category = "UI.Pause")
	TSubclassOf<USRGamePlayWidget> PauseWidgetClass;

	UPROPERTY(VisibleInstanceOnly, Category = "UI.Pause")
	USRGamePlayWidget* PauseWidget;

	UPROPERTY(EditDefaultsOnly, Category = "UI.Rank")
	TSubclassOf<USRCheckRankWidget> CheckRankWidgetClass;

	UPROPERTY(VisibleInstanceOnly, Category = "UI.Rank")
	USRCheckRankWidget* CheckRankWidget;

	UPROPERTY(EditDefaultsOnly, Category = "UI.Rank")
	TSubclassOf<USRRankingWidget> RankingWidgetClass;

	UPROPERTY(VisibleInstanceOnly, Category = "UI.Rank")
	USRRankingWidget* RankingWidget;

	UPROPERTY(EditDefaultsOnly, Category = "UI.WeaponSelect")
	TSubclassOf<USRSelectWeaponWidget> SelectWeaponWidgetClass;

	UPROPERTY(VisibleInstanceOnly, Category = "UI.WeaponSelect")
	USRSelectWeaponWidget* SelectWeaponWidget;

	UPROPERTY(EditDefaultsOnly, Category = "UI.Setting")
	TSubclassOf<USRSettingWidget> SettingWidgetClass;

	UPROPERTY(VisibleInstanceOnly, Category = "UI.Setting")
	USRSettingWidget* SettingWidget;
};