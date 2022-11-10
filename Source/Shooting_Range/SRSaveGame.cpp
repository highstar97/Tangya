#include "SRSaveGame.h"

USRSaveGame::USRSaveGame()
{
	
}

void USRSaveGame::AddRankData(FSRRankData RankData)
{
	RankArray.Emplace(RankData);
	RankArray.StableSort([](const FSRRankData& BackData, const FSRRankData& FrontData){
		return BackData.Score > FrontData.Score;
	});
}

int32 USRSaveGame::CheckRank(FSRRankData TempData)
{
	int32 Rank;
	AddRankData(TempData);
	if (RankArray.Find(TempData, Rank))
	{
		RankArray.RemoveAt(Rank);
		return Rank+1;
	}
	else
	{
		return -1;
	}
}
