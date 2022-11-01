#pragma once

#include "GameFramework/PlayerState.h"
#include "SRPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnPlayerStateChangedDelegate);

UCLASS()
class SHOOTING_RANGE_API ASRPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ASRPlayerState();

	void AddGameScore(int EarnedScore);

	int32 GetGameScore() { return GameScore; }

	FOnPlayerStateChangedDelegate OnPlayerStateChanged;

private:
	UPROPERTY(Transient)
	int32 GameScore;
};
