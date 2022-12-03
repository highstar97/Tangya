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
	void BindPlayerState(ASRPlayerState* PlayerState);

	void SetbGauging(bool NewBoolean) { bGauging = NewBoolean; };

	float GetGauge() { return Gauge; };
	void SetGauge(float NewGauge) { Gauge = NewGauge; }

	void UpdateTimingCatcher();

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void NativeConstruct() override;

	void UpdatePlayerState();

private:
	void AddGauge(float InDeltaTime);
	float GetGaugeRatio();

private:
	TWeakObjectPtr<ASRPlayerState> CurrentPlayerState;

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

	UPROPERTY(VisibleAnywhere)
	float Gauge;

	bool bGauging;


};