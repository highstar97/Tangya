#include "SRGameMode.h"
#include "SRCharacter.h"
#include "SRPlayerController.h"
#include "SRPlayerState.h"

ASRGameMode::ASRGameMode()
{
	DefaultPawnClass = ASRCharacter::StaticClass();
	PlayerControllerClass = ASRPlayerController::StaticClass();
	PlayerStateClass = ASRPlayerState::StaticClass();

	TotalBullets = 10;
	GameMode = EGameMode::BASIC;
}

void ASRGameMode::PostLogin(APlayerController* NewPlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("PostLogin Begin"));
	Super::PostLogin(NewPlayer);
	UE_LOG(LogTemp, Warning, TEXT("PostLogin End"));
}

int32 ASRGameMode::GetTotalBullets()
{
	Super::GetTotalBullets();
	return TotalBullets;
}

void ASRGameMode::NumOfBulletIsZero(ASRPlayerController* Controller)
{
	ensure(nullptr != Controller);
	Controller->OnGameEnd();
	UE_LOG(LogTemp, Error, TEXT("Game End"));
}