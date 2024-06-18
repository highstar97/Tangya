#include "HUDWidget.h"
#include "SRPlayerState.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

UHUDWidget::UHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ChargingSpeed = 150.0f;
}

void UHUDWidget::UpdateTimingCatcher()
{
	if (!ensure(TimingCatcher != nullptr)) return;

	TimingCatcher->SetPercent(GetCurrentGaugeRatio());
}

void UHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bIsGauging)
	{
		AddGauge(InDeltaTime);
		UpdateTimingCatcher();
	}
}

void UHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	bIsGauging = false;
	CurrentGauge = 0.0f;

	ASRPlayerState* SRPlayerState = GetOwningPlayerState<ASRPlayerState>();
	if (SRPlayerState != nullptr)
	{
		SRPlayerState->OnPlayerStateChanged.AddUObject(this, &UHUDWidget::UpdatePlayerState);
	}
}

void UHUDWidget::UpdatePlayerState()
{
	ASRPlayerState* SRPlayerState = GetOwningPlayerState<ASRPlayerState>();
	if (SRPlayerState == nullptr) return;

	Score->SetText(FText::FromString(FString::FromInt(FMath::FloorToInt(SRPlayerState->GetScore()))));
	CurrentBullets->SetText(FText::FromString(FString::FromInt(SRPlayerState->GetNumOfCurrentBullets())));
	TotalBullets->SetText(FText::FromString(FString("/ ") + FString::FromInt(SRPlayerState->GetNumOfTotalBullets())));
}

void UHUDWidget::AddGauge(float InDeltaTime)
{
	CurrentGauge += ChargingSpeed * InDeltaTime;
	
	if (CurrentGauge > 200.0f)
	{
		CurrentGauge = 0.0f;
	}
}

float UHUDWidget::GetCurrentGaugeRatio()
{
	if (CurrentGauge >= 0.0f && CurrentGauge <= 100.0f)
	{
		return CurrentGauge / 100.0f;
	}
	else if (CurrentGauge > 100.0f && CurrentGauge <= 200.0f)
	{
		return (200.0f - CurrentGauge) / 100.0f;
	}
	return -1.0f;
}
