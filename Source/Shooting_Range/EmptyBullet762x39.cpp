#include "EmptyBullet762x39.h"
#include "GameFramework/ProjectileMovementComponent.h"

AEmptyBullet762x39::AEmptyBullet762x39()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> EMPTYBULLET762X39(TEXT("/Game/FPS_Weapon_Bundle/Weapons/Meshes/Ammunition/SM_Shell_762x39_Empty.SM_Shell_762x39_Empty"));
	if (EMPTYBULLET762X39.Succeeded())
	{
		EmptyShell->SetStaticMesh(EMPTYBULLET762X39.Object);
	}
}

void AEmptyBullet762x39::BounceOff(const FVector& ShootDirection)
{
	Super::BounceOff(ShootDirection);

	FVector Base = ShootDirection * ProjectileMovementComponent->InitialSpeed;
	ProjectileMovementComponent->Velocity = FVector(-Base.Y, Base.X, Base.Z);
}