#include "SRPlayerController.h"

void ASRPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	UE_LOG(LogTemp, Log, TEXT("Player Controller PostInitializeComponetns"));
}

void ASRPlayerController::OnPossess(APawn* aPawn)
{
	UE_LOG(LogTemp, Log, TEXT("Player Controller OnPossess"));
	Super::OnPossess(aPawn);
}
