#include "SRRankingWidget.h"
#include "RankInfoData.h"
#include "SRSaveGame.h"
#include "SRPlayerController.h"
#include "Components/ListView.h"
#include "Kismet/GameplayStatics.h"

void USRRankingWidget::UpdateWidget()
{
	List_Rank->ClearListItems();

	USRSaveGame* SRSaveGame = Cast<USRSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Save1"), 0));
	if (nullptr == SRSaveGame)
	{
		UE_LOG(LogTemp, Error, TEXT("SaveGame Error In RankingWidget"));
		SRSaveGame = GetMutableDefault<USRSaveGame>();
	}

	TArray<FSRRankData> Temp = SRSaveGame->GetRankArray();
	for (int32 i = 0; i < Temp.Num(); ++i)
	{
		URankInfoData* RankInfoData = NewObject<URankInfoData>(this, URankInfoData::StaticClass());
		RankInfoData->SetRank(i + 1);
		RankInfoData->SetName(Temp[i].Name);
		RankInfoData->SetScore(Temp[i].Score);
		RankInfoData->SetComment(Temp[i].Comment);
		List_Rank->AddItem(RankInfoData);
	}
}