#pragma once

#include "GameFramework/Actor.h"
#include "SRBullet.generated.h"

class UProjectileMovementComponent;

UCLASS()
class SHOOTING_RANGE_API ASRBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	ASRBullet();

protected:
	virtual void BeginPlay() override;

public:
	virtual void FireInDirection(const FVector& ShootDirection);

protected:
	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	UStaticMeshComponent* Shell;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	UProjectileMovementComponent* ProjectileMovementComponent;
};