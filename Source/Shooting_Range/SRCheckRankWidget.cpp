#include "SRCheckRankWidget.h"
#include "SRPlayerController.h"
#include "SRPlayerState.h"
#include "SRSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"

void USRCheckRankWidget::UpdateWidget()
{
	FSRRankData TempData;
	TempData.Name = TEXT("Checking");
	TempData.Score = Cast<ASRPlayerController>(GetOwningPlayer())->GetPlayerState()->GetGameScore();
	TempData.Comment = TEXT("Checking");

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
		UE_LOG(LogTemp, Warning, TEXT("Name is null"));
		return;
	}
	if (ET_Comment->GetText().IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Comment is null"));
		return;
	}

	ASRPlayerController* OwningPlayerController = Cast<ASRPlayerController>(GetOwningPlayer());

	FSRRankData NewRankData;
	NewRankData.Name = ET_Name->GetText().ToString();
	NewRankData.Score = OwningPlayerController->GetPlayerState()->GetGameScore();
	NewRankData.Comment = ET_Comment->GetText().ToString();
	
	SaveGame->AddRankData(NewRankData);
	if (!UGameplayStatics::SaveGameToSlot(SaveGame, TEXT("Save1"), 0))
	{
		UE_LOG(LogTemp, Error, TEXT("SaveGame Error!"));
	}

	RemoveFromParent();
	OwningPlayerController->ShowRankingWidget();
}

void USRCheckRankWidget::PressedNo()
{
	// Add WarningWidget to Viewport?
}