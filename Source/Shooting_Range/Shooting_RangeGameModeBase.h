#pragma once

#include "GameFramework/GameModeBase.h"
#include "Shooting_RangeGameModeBase.generated.h"

class ASRPlayerController;

UCLASS()
class SHOOTING_RANGE_API AShooting_RangeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AShooting_RangeGameModeBase();

	virtual void PostLogin(APlayerController* NewPlayer) override;

	void NumOfBulletIsZero(ASRPlayerController* Controller);

	int32 GetTotalBullets() { return TotalBullets; }

private:
	UPROPERTY()
	int32 TotalBullets;
};
