#pragma once

#include "GameFramework/GameModeBase.h"
#include "Shooting_RangeGameModeBase.generated.h"

UCLASS()
class SHOOTING_RANGE_API AShooting_RangeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AShooting_RangeGameModeBase();

	virtual void PostLogin(APlayerController* NewPlayer) override;

	int32 GetTotalBullets() { return TotalBullets; }

private:
	UPROPERTY()
	int32 TotalBullets;
};
