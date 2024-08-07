#include "SRBullet.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"

ASRBullet::ASRBullet()
{
	PrimaryActorTick.bCanEverTick = false;

	Shell = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shell"));
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

	SetRootComponent(Shell);

	Shell->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	ProjectileMovementComponent->InitialSpeed = 10.0f;
	ProjectileMovementComponent->ProjectileGravityScale = 1.0f;
	ProjectileMovementComponent->bShouldBounce = false;

	Shell->SetCollisionProfileName(TEXT("Bullet"));
}

void ASRBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASRBullet::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}