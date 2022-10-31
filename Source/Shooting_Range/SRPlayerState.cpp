#include "SRPlayerState.h"

ASRPlayerState::ASRPlayerState()
{
	GameScore = 0;
}

void ASRPlayerState::AddGameScore(int EarnedScore)
{
	GameScore += EarnedScore;
}