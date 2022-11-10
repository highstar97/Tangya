#pragma once

#include "GameFramework/Actor.h"
#include "SRWeapon.generated.h"

class ASRBullet;
class ASREmptyBullet;

UCLASS()
class SHOOTING_RANGE_API ASRWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASRWeapon();

	virtual USkeletalMeshComponent* GetMesh() { return Mesh; }
	virtual USoundWave* GetAttackSound() { return AttackSound; }

	virtual ASRBullet* ShootBullet(UWorld* World, FVector MuzzleLocation, FRotator MuzzleRotation, FActorSpawnParameters SpawnParams);
	virtual ASREmptyBullet* ShootEmptyBullet(UWorld* World, FVector ShellEjectLocation, FRotator ShellEjectRotation, FActorSpawnParameters SpawnParams);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = Sound)
	USoundWave* AttackSound;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	ASRBullet* Bullet;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	ASREmptyBullet* EmptyBullet;
};
