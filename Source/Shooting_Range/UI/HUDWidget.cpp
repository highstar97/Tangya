#include "HUDWidget.h"
#include "SRPlayerState.h"
#include "Components/TextBlock.h"

void UHUDWidget::BindPlayerState(ASRPlayerState* PlayerState)
{
	if (nullptr == PlayerState)
	{
		return;
	}

	CurrentPlayerState = PlayerState;
	PlayerState->OnPlayerStateChanged.AddUObject(this, &UHUDWidget::UpdatePlayerState);
}

void UHUDWidget::NativeConstruct()
{

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
