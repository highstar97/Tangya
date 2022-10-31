#include "Shooting_RangeGameModeBase.h"
#include "SRCharacter.h"
#include "SRPlayerController.h"

AShooting_RangeGameModeBase::AShooting_RangeGameModeBase()
{
	DefaultPawnClass = ASRCharacter::StaticClass();
	PlayerControllerClass = ASRPlayerController::StaticClass();
}

void AShooting_RangeGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("PostLogin Begin"));
	Super::PostLogin(NewPlayer);
	UE_LOG(LogTemp, Warning, TEXT("PostLogin End"));
}
