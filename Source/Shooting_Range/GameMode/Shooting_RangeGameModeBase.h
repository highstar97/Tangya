#pragma once

#include "GameFramework/GameModeBase.h"
#include "Shooting_RangeGameModeBase.generated.h"

enum class EGameMode
{
	BASE,
	BASIC,
	INF,
};

UCLASS()
class SHOOTING_RANGE_API AShooting_RangeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AShooting_RangeGameModeBase();

	virtual void PostLogin(APlayerController* NewPlayer) override;

	int32 GetTotalBullets() { return TotalBullets; }

	EGameMode GetGameMode() { return GameMode; }

protected:
	UPROPERTY()
	int32 TotalBullets;

	EGameMode GameMode;
};
