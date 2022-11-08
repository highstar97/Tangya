#pragma once

#include "GameFramework/PlayerState.h"
#include "SRPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnPlayerStateChangedDelegate);

class ASRPlayerController;

UCLASS()
class SHOOTING_RANGE_API ASRPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ASRPlayerState();

	void BindPlayerController(ASRPlayerController* Controller) { PlayerController = Controller; };

	void AddGameScore(int EarnedScore);
	int32 GetGameScore() { return GameScore; }

	void SetCurrentBullets(int32 NumOfBullets);
	int32 GetCurrentBullets() { return CurrentBullets; }

	void SetTotalBullets(int32 NumOfBullets);
	int32 GetTotalBullets() { return TotalBullets; }

	FOnPlayerStateChangedDelegate OnPlayerStateChanged;

private:
	UPROPERTY()
	ASRPlayerController* PlayerController;

	UPROPERTY(Transient)
	int32 GameScore;

	UPROPERTY(Transient)
	int32 CurrentBullets;

	UPROPERTY(Transient)
	int32 TotalBullets;
};
