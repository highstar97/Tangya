#pragma once

#include "GameFramework/PlayerState.h"
#include "SRPlayerState.generated.h"

UCLASS()
class SHOOTING_RANGE_API ASRPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ASRPlayerState();

	void AddGameScore(int EarnedScore);

private:
	UPROPERTY(Transient)
	int32 GameScore;
};
