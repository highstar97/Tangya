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

public:
	void SetNumOfCurrentBullets(const int32 _NumOfCurrentBullets);
	int32 GetNumOfCurrentBullets() const { return NumOfCurrentBullets; }

	void SetNumOfTotalBullets(const int32 _NumOfTotalBullets);
	int32 GetNumOfTotalBullets() const { return NumOfTotalBullets; }

public:
	void AddScore(const float AdditionalScore);

public:
	FOnPlayerStateChangedDelegate OnPlayerStateChanged;

private:
	UPROPERTY(VisibleAnywhere, Category = "Bullet", Transient)
	int32 NumOfCurrentBullets;

	UPROPERTY(VisibleAnywhere, Category = "Bullet", Transient)
	int32 NumOfTotalBullets;
};