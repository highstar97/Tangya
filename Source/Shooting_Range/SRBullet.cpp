#include "SRBullet.h"
#include "GameFramework/ProjectileMovementComponent.h"

ASRBullet::ASRBullet()
{
	PrimaryActorTick.bCanEverTick = false;

	Shell = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SHELL"));
	EmptyShell = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EMPTYSHELL"));
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("PROJECTILEMOVEMENT"));

	SetRootComponent(Shell);

	Shell->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	EmptyShell->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	ProjectileMovementComponent->InitialSpeed = 10.0f;
	ProjectileMovementComponent->ProjectileGravityScale = 1.0f;
	ProjectileMovementComponent->bShouldBounce = false;
}

void ASRBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASRBullet::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}