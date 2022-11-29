#pragma once

#include "GameFramework/Actor.h"
#include "SREmptyBullet.generated.h"

class UProjectileMovementComponent;

UCLASS()
class SHOOTING_RANGE_API ASREmptyBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	ASREmptyBullet();

protected:
	virtual void BeginPlay() override;

public:
	virtual void BounceOff(const FVector& ShootDirection);

protected:
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UStaticMeshComponent* EmptyShell;

	UPROPERTY(VisibleAnywhere, Category = Projectile)
	UProjectileMovementComponent* ProjectileMovementComponent;
};
