#pragma once

#include "Shooting_RangeGameModeBase.h"
#include "SRInfinityGameMode.generated.h"

UCLASS()
class SHOOTING_RANGE_API ASRInfinityGameMode : public AShooting_RangeGameModeBase
{
	GENERATED_BODY()
	
public:
	ASRInfinityGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;
};
