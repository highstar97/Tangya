#include "Shooting_RangeGameModeBase.h"
#include "SRCharacter.h"
#include "SRPlayerController.h"
#include "SRPlayerState.h"

AShooting_RangeGameModeBase::AShooting_RangeGameModeBase()
{
	DefaultPawnClass = ASRCharacter::StaticClass();
	PlayerControllerClass = ASRPlayerController::StaticClass();
	PlayerStateClass = ASRPlayerState::StaticClass();

	TotalBullets = 0;
	GameMode = EGameMode::BASE;
}

void AShooting_RangeGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("PostLogin Begin"));
	Super::PostLogin(NewPlayer);
	UE_LOG(LogTemp, Warning, TEXT("PostLogin End"));
}