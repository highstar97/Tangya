#include "SRRankingWidget.h"

#include "Components/ListView.h"
#include "Kismet/GameplayStatics.h"

#include "SRSaveGame.h"
#include "RankInfoData.h"

void USRRankingWidget::UpdateWidget()
{
	List_Rank->ClearListItems();

	USRSaveGame* SRSaveGame = Cast<USRSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Save1"), 0));
	if (SRSaveGame == nullptr)
	{
		SRSaveGame = GetMutableDefault<USRSaveGame>();
	}

	TArray<FSRRankData> Rank = SRSaveGame->GetRankArray();
	for (int32 i = 0; i < Rank.Num(); ++i)
	{
		URankInfoData* RankInfo = NewObject<URankInfoData>(this, URankInfoData::StaticClass());
		RankInfo->SetRank(i + 1);
		RankInfo->SetName(Rank[i].Name);
		RankInfo->SetScore(Rank[i].Score);
		RankInfo->SetComment(Rank[i].Comment);
		List_Rank->AddItem(RankInfo);
	}
}