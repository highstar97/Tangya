#include "HUDWidget.h"
#include "SRPlayerState.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UHUDWidget::BindPlayerState(ASRPlayerState* PlayerState)
{
	if (nullptr == PlayerState)
	{
		return;
	}

	CurrentPlayerState = PlayerState;
	PlayerState->OnPlayerStateChanged.AddUObject(this, &UHUDWidget::UpdatePlayerState);
}

void UHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bGauging)
	{
		AddGauge();
		UpdateTimingCatcher();
	}
}

void UHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Gauge = 0.0f;
	bGauging = false;
}

void UHUDWidget::UpdatePlayerState()
{
	if (nullptr == CurrentPlayerState)
	{
		return;
	}

	Score->SetText(FText::FromString(FString::FromInt(CurrentPlayerState->GetGameScore())));
	CurrentBullets->SetText(FText::FromString(FString::FromInt(CurrentPlayerState->GetCurrentBullets())));
	TotalBullets->SetText(FText::FromString(FString("/ ") + FString::FromInt(CurrentPlayerState->GetTotalBullets())));
}

void UHUDWidget::UpdateTimingCatcher()
{
	if (nullptr == TimingCatcher)
	{
		return;
	}

	TimingCatcher->SetPercent(GetGaugeRatio());
}

void UHUDWidget::AddGauge()
{
	Gauge += 8.0f;
	
	if (Gauge > 200.0f)
	{
		Gauge = 0.0f;
	}
}

float UHUDWidget::GetGaugeRatio()
{
	if (Gauge >= 0.0f && Gauge <= 100.0f)
	{
		return Gauge / 100.0f;
	}
	else if (Gauge > 100.0f && Gauge <= 200.0f)
	{
		return (200.0f - Gauge) / 100.0f;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Gauge Error"));
		return 0.0f;
	}
}
