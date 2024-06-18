#pragma once

#include "SRWeapon.h"
#include "AR4_X.generated.h"

UCLASS()
class SHOOTING_RANGE_API AAR4_X : public ASRWeapon
{
	GENERATED_BODY()
	
public:
	AAR4_X();

	virtual ASRBullet* ShootBullet(UWorld* World, FVector MuzzleLocation, FRotator MuzzleRotation, FActorSpawnParameters SpawnParams) override;
	virtual ASREmptyBullet* ShootEmptyBullet(UWorld* World, FVector ShellEjectLocation, FRotator ShellEjectRotation, FActorSpawnParameters SpawnParams) override;
};