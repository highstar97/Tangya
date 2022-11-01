#include "SRPlayerState.h"

ASRPlayerState::ASRPlayerState()
{
	GameScore = 0;
	CurrentBullets = 1;
	TotalBullets = 2;
}

void ASRPlayerState::AddGameScore(int EarnedScore)
{
	GameScore += EarnedScore;
	OnPlayerStateChanged.Broadcast();
}

void ASRPlayerState::SetCurrentBullets(int32 NumOfBullets)
{
	CurrentBullets = NumOfBullets;
	OnPlayerStateChanged.Broadcast();

	if (NumOfBullets == 0)
	{
		// 게임모드 -> 게임 종료
		UE_LOG(LogTemp, Error, TEXT("Game End"));
	}
}

void ASRPlayerState::SetTotalBullets(int32 NumOfBullets)
{
	TotalBullets = NumOfBullets;
	OnPlayerStateChanged.Broadcast();
}