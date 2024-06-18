#include "SRPlayerState.h"

#include "SRCompetitionGameMode.h"

ASRPlayerState::ASRPlayerState()
{
	SetScore(0.0f);
	NumOfCurrentBullets = -1;
	NumOfTotalBullets = -1;
}

void ASRPlayerState::SetNumOfCurrentBullets(const int32 _NumOfCurrentBullets)
{
	NumOfCurrentBullets = _NumOfCurrentBullets;
	OnPlayerStateChanged.Broadcast();

	ASRCompetitionGameMode* SRGameMode = Cast<ASRCompetitionGameMode>(GetWorld()->GetAuthGameMode());
	if (SRGameMode == nullptr || SRGameMode->GetCurrentMode() != EGameMode::Competition) return;

	if (SRGameMode->IsGameEnded(NumOfCurrentBullets))
	{
		SRGameMode->EndGame();
	}
}

void ASRPlayerState::SetNumOfTotalBullets(const int32 _NumOfTotalBullets)
{
	NumOfTotalBullets = _NumOfTotalBullets;
	OnPlayerStateChanged.Broadcast();
}

void ASRPlayerState::AddScore(const float AdditionalScore)
{
	SetScore(GetScore() + AdditionalScore);
	OnPlayerStateChanged.Broadcast();
}