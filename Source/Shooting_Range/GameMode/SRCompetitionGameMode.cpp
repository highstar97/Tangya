#include "SRCompetitionGameMode.h"

#include "SRPlayerController.h"

ASRCompetitionGameMode::ASRCompetitionGameMode()
{
	CurrentMode = EGameMode::Competition;
	EndCondition = 0;
}

void ASRCompetitionGameMode::EndGame()
{
	ASRPlayerController* SRPlayerController = GetWorld()->GetFirstPlayerController<ASRPlayerController>();
	if (!ensure(SRPlayerController != nullptr)) return;

	SRPlayerController->OnGameEnd();
}

bool ASRCompetitionGameMode::IsGameEnded(const int32 NumOfCurrentBullets)
{
	if (NumOfCurrentBullets <= EndCondition)
		return true;
	else
		return false;
}