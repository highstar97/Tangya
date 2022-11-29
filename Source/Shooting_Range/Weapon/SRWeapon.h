#pragma once

#include "GameFramework/Actor.h"
#include "SRWeapon.generated.h"

class ASRBullet;
class ASREmptyBullet;
class UParticleSystem;

enum class EWeaponAbilityScore
{
	NONE = 0,
	ADD1 = 1,
	ADD2 = 2,
};

enum class EWeaponAbilityBullet
{
	NONE = 0,
	ADD3 = 3,
	SUBTRACT3 = -3,
};

UCLASS()
class SHOOTING_RANGE_API ASRWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASRWeapon();

	virtual UTexture2D* GetImage() { return Image; }
	virtual FString GetName() { return Name; }
	virtual FString GetAbility() { return Ability; }
	virtual USkeletalMeshComponent* GetMesh() { return Mesh; }
	virtual UParticleSystem* GetMuzzleParticle() { return MuzzleParticle; }
	UParticleSystem* GetBulletTrailParticle() { return BulletTrailParticle; }
	virtual USoundWave* GetAttackSound() { return AttackSound; }
	virtual EWeaponAbilityScore GetWeaponAbilityScore() { return WeaponAbilityScore; }
	virtual EWeaponAbilityBullet GetWeaponAbilityBullet() { return WeaponAbilityBullet; }

	virtual ASRBullet* ShootBullet(UWorld* World, FVector MuzzleLocation, FRotator MuzzleRotation, FActorSpawnParameters SpawnParams);
	virtual ASREmptyBullet* ShootEmptyBullet(UWorld* World, FVector ShellEjectLocation, FRotator ShellEjectRotation, FActorSpawnParameters SpawnParams);

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	TSubclassOf<ASRWeapon> WeaponClass;

protected:
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	UTexture2D* Image;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	FString Name;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	FString Ability;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = Particle)
	UParticleSystem* MuzzleParticle;

	UPROPERTY(VisibleAnywhere, Category = Particle)
	UParticleSystem* BulletTrailParticle;

	UPROPERTY(VisibleAnywhere, Category = Sound)
	USoundWave* AttackSound;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	ASRBullet* Bullet;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	ASREmptyBullet* EmptyBullet;

	EWeaponAbilityScore WeaponAbilityScore = EWeaponAbilityScore::NONE;

	EWeaponAbilityBullet WeaponAbilityBullet = EWeaponAbilityBullet::NONE;
};