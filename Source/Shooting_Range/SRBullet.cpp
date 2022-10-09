#include "SRBullet.h"

ASRBullet::ASRBullet()
{
	PrimaryActorTick.bCanEverTick = false;

	Shell = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SHELL"));
	EmptyShell = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EMPTYSHELL"));
}

void ASRBullet::BeginPlay()
{
	Super::BeginPlay();
	
}