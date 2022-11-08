#include "Shooting_RangeGameModeBase.h"
#include "SRCharacter.h"
#include "SRPlayerController.h"
#include "SRPlayerState.h"

AShooting_RangeGameModeBase::AShooting_RangeGameModeBase()
{
	DefaultPawnClass = ASRCharacter::StaticClass();
	PlayerControllerClass = ASRPlayerController::StaticClass();
	PlayerStateClass = ASRPlayerState::StaticClass();

	TotalBullets = 10;
}

void AShooting_RangeGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("PostLogin Begin"));
	Super::PostLogin(NewPlayer);
	UE_LOG(LogTemp, Warning, TEXT("PostLogin End"));
}

void AShooting_RangeGameModeBase::NumOfBulletIsZero(ASRPlayerController* Controller)
{
	ensure(nullptr != Controller);
	Controller->OnGameEnd();
	UE_LOG(LogTemp, Error, TEXT("Game End"));
}
