#include "SRInfinityGameMode.h"
#include "SRCharacter.h"
#include "SRPlayerController.h"
#include "SRPlayerState.h"

ASRInfinityGameMode::ASRInfinityGameMode()
{
	DefaultPawnClass = ASRCharacter::StaticClass();
	PlayerControllerClass = ASRPlayerController::StaticClass();
	PlayerStateClass = ASRPlayerState::StaticClass();

	TotalBullets = 100;
	GameMode = EGameMode::INF;
}

void ASRInfinityGameMode::PostLogin(APlayerController* NewPlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("PostLogin Begin"));
	Super::PostLogin(NewPlayer);
	UE_LOG(LogTemp, Warning, TEXT("PostLogin End"));
}