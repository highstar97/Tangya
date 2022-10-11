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
	void FireInDirection(const FVector& ShootDirection);

protected:
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UStaticMeshComponent* Shell;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UStaticMeshComponent* EmptyShell;

	UPROPERTY(VisibleAnywhere, Category = Projectile)
	UProjectileMovementComponent* ProjectileMovementComponent;
};