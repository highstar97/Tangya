#include "SRSaveGame.h"

USRSaveGame::USRSaveGame()
{
	SettingData.Sound = 1.0f;
	SettingData.Light = 1.0f;
	SettingData.MouseSensitivity = 1.0f;
}

void USRSaveGame::AddRankData(FSRRankData RankData)
{
	RankArray.Emplace(RankData);
	RankArray.StableSort([](const FSRRankData& BackData, const FSRRankData& FrontData){
		return BackData.Score > FrontData.Score;
	});
}

void USRSaveGame::UpdateSettingData(float NewSound, float NewLight, float NewMouseSensitivity)
{
	SettingData.Sound = NewSound;
	SettingData.Light = NewLight;
	SettingData.MouseSensitivity = NewMouseSensitivity;
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
