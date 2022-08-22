#include "Shooting_RangeGameModeBase.h"
#include "SRCharacter.h"

AShooting_RangeGameModeBase::AShooting_RangeGameModeBase()
{
	DefaultPawnClass = ASRCharacter::StaticClass();
}