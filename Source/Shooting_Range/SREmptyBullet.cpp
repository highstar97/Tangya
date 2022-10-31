#include "SREmptyBullet.h"
#include "Gameframework/ProjectileMovementComponent.h"

ASREmptyBullet::ASREmptyBullet()
{
	PrimaryActorTick.bCanEverTick = false;

	EmptyShell = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EMPTYSHELL"));
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("PROJECTILEMOVEMENT"));

	SetRootComponent(EmptyShell);

	EmptyShell->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	ProjectileMovementComponent->InitialSpeed = 200.0f;
	ProjectileMovementComponent->ProjectileGravityScale = 1.0f;
	ProjectileMovementComponent->bShouldBounce = true;

	EmptyShell->SetCollisionProfileName(TEXT("EmptyBullet"));
}

void ASREmptyBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASREmptyBullet::BounceOff(const FVector& ShootDirection)
{
	FVector Base = ShootDirection * ProjectileMovementComponent->InitialSpeed;
	ProjectileMovementComponent->Velocity = FVector(-Base.Y, Base.X, Base.Z);
}