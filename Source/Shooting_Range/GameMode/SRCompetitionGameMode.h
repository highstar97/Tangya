#pragma once

#include "SRBaseGameMode.h"
#include "SRCompetitionGameMode.generated.h"

class ASRPlayerController;

UCLASS()
class SHOOTING_RANGE_API ASRCompetitionGameMode : public ASRBaseGameMode
{
	GENERATED_BODY()

public:
	ASRCompetitionGameMode();

public:
	void EndGame();

	bool IsGameEnded(const int32 NumOfCurrentBullets);

private:
	// When PlayerState.NumOfCurrentBulltes <= EndCondition, Game be Ended
	UPROPERTY(VisibleAnywhere, Category = "Rule")
	int32 EndCondition;
};