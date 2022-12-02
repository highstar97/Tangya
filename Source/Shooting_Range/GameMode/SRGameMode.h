#pragma once

#include "Shooting_RangeGameModeBase.h"
#include "SRGameMode.generated.h"

class ASRPlayerController;

UCLASS()
class SHOOTING_RANGE_API ASRGameMode : public AShooting_RangeGameModeBase
{
	GENERATED_BODY()

public:
	ASRGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual int32 GetTotalBullets() override;

	void NumOfBulletIsZero(ASRPlayerController* Controller);
};