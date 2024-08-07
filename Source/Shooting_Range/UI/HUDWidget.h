#pragma once

#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

class ASRPlayerState;
class UTextBlock;
class UProgressBar;

UCLASS()
class SHOOTING_RANGE_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UHUDWidget(const FObjectInitializer& ObjectInitializer);

public:
	void SetbIsGauging(const bool _bIsGauging) { bIsGauging = _bIsGauging; };

	float GetCurrentGauge() const { return CurrentGauge; };

	void SetCurrentGauge(const float _NewGauge) { CurrentGauge = _NewGauge; }

public:
	void UpdateTimingCatcher();

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void NativeConstruct() override;

private:
	void UpdatePlayerState();

	void AddGauge(float InDeltaTime);

	float GetCurrentGaugeRatio();

private:
	UPROPERTY(VisibleAnywhere, Category = "Gauge")
	bool bIsGauging;

	UPROPERTY(EditAnywhere, Category = "Gauge")
	float ChargingSpeed;

	UPROPERTY(VisibleAnywhere, Category = "Gauge")
	float CurrentGauge;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Score;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* HighScore;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrentBullets;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TotalBullets;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* TimingCatcher;
};