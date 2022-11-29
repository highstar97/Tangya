#include "SRBullet.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"

ASRBullet::ASRBullet()
{
	PrimaryActorTick.bCanEverTick = false;

	Shell = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SHELL"));
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("PROJECTILEMOVEMENT"));

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

void ASRBullet::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ASRBullet::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}