#include "SRCheckRankWidget.h"

#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

#include "SRSaveGame.h"
#include "SRPlayerState.h"
#include "SRPlayerController.h"

void USRCheckRankWidget::UpdateWidget()
{
	FSRRankData TempData;
	TempData.Name = TEXT("Checking...");
	TempData.Score = Cast<ASRPlayerController>(GetOwningPlayer())->GetPlayerState<ASRPlayerState>()->GetScore();
	TempData.Comment = TEXT("Checking...");

	Text_FinalScore->SetText(FText::FromString(FString::FromInt(TempData.Score)));
	Text_FinalRank->SetText(FText::FromString(FString::FromInt(SaveGame->CheckRank(TempData))));
}

void USRCheckRankWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SaveGame = Cast<USRSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Save1"), 0));
	if (nullptr == SaveGame)
	{
		SaveGame = GetMutableDefault<USRSaveGame>();
	}
}

void USRCheckRankWidget::PressedYes()
{
	if (ET_Name->GetText().IsEmpty())
	{
		ET_Name->SetToolTipText(FText::FromString("Write Your Name"));
		return;
	}

	if (ET_Comment->GetText().IsEmpty())
	{
		ET_Comment->SetToolTipText(FText::FromString("Write Your Comment"));
		return;
	}

	ASRPlayerController* SRPlayerController = Cast<ASRPlayerController>(GetOwningPlayer());
	if (!ensure(SRPlayerController != nullptr)) return;

	FSRRankData NewRankData;
	NewRankData.Name = ET_Name->GetText().ToString();
	NewRankData.Score = SRPlayerController->GetPlayerState<ASRPlayerState>()->GetScore();
	NewRankData.Comment = ET_Comment->GetText().ToString();
	
	if (!ensure(SaveGame != nullptr)) return;
	SaveGame->AddRankData(NewRankData);

	if (!UGameplayStatics::SaveGameToSlot(SaveGame, TEXT("Save1"), 0))
	{
		UE_LOG(LogTemp, Error, TEXT("SaveGame Error!"));
	}

	SRPlayerController->ToggleCheckRankWidget(false);
	SRPlayerController->RegisterRanking();
}

void USRCheckRankWidget::PressedNo()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainLobby"));
}