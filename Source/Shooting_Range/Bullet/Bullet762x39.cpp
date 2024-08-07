#include "Bullet762x39.h"
#include "GameFramework/ProjectileMovementComponent.h"

ABullet762x39::ABullet762x39()
{
	ProjectileMovementComponent->InitialSpeed = 7620.0f;
}

void ABullet762x39::FireInDirection(const FVector& ShootDirection)
{
	Super::FireInDirection(ShootDirection);
}