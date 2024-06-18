#pragma once

#include "SRWeapon.h"
#include "KA47_X.generated.h"

UCLASS()
class SHOOTING_RANGE_API AKA47_X : public ASRWeapon
{
	GENERATED_BODY()

public:
	AKA47_X();

	virtual ASRBullet* ShootBullet(UWorld* World, FVector MuzzleLocation, FRotator MuzzleRotation, FActorSpawnParameters SpawnParams) override;
	virtual ASREmptyBullet* ShootEmptyBullet(UWorld* World, FVector ShellEjectLocation, FRotator ShellEjectRotation, FActorSpawnParameters SpawnParams) override;
};