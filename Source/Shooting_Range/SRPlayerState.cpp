#include "SRPlayerState.h"
#include "Shooting_RangeGameModeBase.h"

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
		auto GameMode = Cast<AShooting_RangeGameModeBase>(GetWorld()->GetAuthGameMode());
		GameMode->NumOfBulletIsZero(PlayerController);		
	}
}

void ASRPlayerState::SetTotalBullets(int32 NumOfBullets)
{
	TotalBullets = NumOfBullets;
	OnPlayerStateChanged.Broadcast();
}