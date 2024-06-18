#include "SRBaseGameMode.h"

#include "SRPlayerState.h"
#include "SRPlayerController.h"
#include "SRCharacter.h"

ASRBaseGameMode::ASRBaseGameMode()
{
	DefaultPawnClass = ASRCharacter::StaticClass();
	PlayerControllerClass = ASRPlayerController::StaticClass();
	PlayerStateClass = ASRPlayerState::StaticClass();

	CurrentMode = EGameMode::BASE;
}