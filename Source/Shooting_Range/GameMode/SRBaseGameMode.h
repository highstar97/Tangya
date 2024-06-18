#pragma once

#include "GameFramework/GameModeBase.h"
#include "SRBaseGameMode.generated.h"

UENUM()
enum class EGameMode
{
	BASE,
	Competition,
	INF
};

UCLASS()
class SHOOTING_RANGE_API ASRBaseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASRBaseGameMode();

public:
	EGameMode GetCurrentMode() const { return CurrentMode; }

protected:
	EGameMode CurrentMode;
};
