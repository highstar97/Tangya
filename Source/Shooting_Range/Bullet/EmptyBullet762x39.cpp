#include "EmptyBullet762x39.h"

AEmptyBullet762x39::AEmptyBullet762x39()
{
}

void AEmptyBullet762x39::BounceOff(const FVector& ShootDirection)
{
	Super::BounceOff(ShootDirection);
}