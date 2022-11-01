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
}

void ASRPlayerState::SetTotalBullets(int32 NumOfBullets)
{
	TotalBullets = NumOfBullets;
	OnPlayerStateChanged.Broadcast();
}