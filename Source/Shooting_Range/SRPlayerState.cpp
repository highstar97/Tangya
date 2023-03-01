#include "SRPlayerState.h"
#include "Shooting_RangeGameModeBase.h"
#include "SRGameMode.h"
#include "SRInfinityGameMode.h"

ASRPlayerState::ASRPlayerState()
{
	GameScore = 0;
	CurrentBullets = 1;
	TotalBullets = 2;
}

void ASRPlayerState::AddGameScore(int32 EarnedScore)
{
	GameScore += EarnedScore;
	OnPlayerStateChanged.Broadcast();
}

// End when the CurrentBullets is zero
void ASRPlayerState::SetCurrentBullets(int32 NumOfBullets)
{
	CurrentBullets = NumOfBullets;
	OnPlayerStateChanged.Broadcast();

	auto GameMode = Cast<AShooting_RangeGameModeBase>(GetWorld()->GetAuthGameMode());
	switch (GameMode->GetGameMode())
	{
	case(EGameMode::BASE):
	{
		break;
	}
	case(EGameMode::BASIC):
	{
		if (NumOfBullets == 0)
		{
			Cast<ASRGameMode>(GameMode)->NumOfBulletIsZero(PlayerController);
		}
		break;
	}
	case(EGameMode::INF):
	{
		break;
	}
	default:
	{
		break;
	}
	}
}

void ASRPlayerState::SetTotalBullets(int32 NumOfBullets)
{
	TotalBullets = NumOfBullets;
	OnPlayerStateChanged.Broadcast();
}