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

	UTexture2D* GetImage() { return Image; }
	FString GetName() { return Name; }
	FString GetAbility() { return Ability; }
	USkeletalMeshComponent* GetMesh() { return Mesh; }
	UParticleSystem* GetMuzzleParticle() { return MuzzleParticle; }
	UParticleSystem* GetBulletTrailParticle() { return BulletTrailParticle; }
	USoundWave* GetAttackSound() { return AttackSound; }
	EWeaponAbilityScore GetWeaponAbilityScore() { return WeaponAbilityScore; }
	EWeaponAbilityBullet GetWeaponAbilityBullet() { return WeaponAbilityBullet; }

	ASRBullet* ShootBullet(UWorld* World, FVector MuzzleLocation, FRotator MuzzleRotation, FActorSpawnParameters SpawnParams);
	ASREmptyBullet* ShootEmptyBullet(UWorld* World, FVector ShellEjectLocation, FRotator ShellEjectRotation, FActorSpawnParameters SpawnParams);

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	TSubclassOf<ASRWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon | Bullet")
	TSubclassOf<ASRBullet> BulletClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon | Bullet")
	TSubclassOf<ASREmptyBullet> EmptyBulletClass;

protected:
	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	UTexture2D* Image;

	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	FString Name;

	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	FString Ability;

	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, Category = Particle)
	UParticleSystem* MuzzleParticle;

	UPROPERTY(EditDefaultsOnly, Category = Particle)
	UParticleSystem* BulletTrailParticle;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundWave* AttackSound;

	UPROPERTY()
	ASRBullet* Bullet;

	UPROPERTY()
	ASREmptyBullet* EmptyBullet;

	EWeaponAbilityScore WeaponAbilityScore = EWeaponAbilityScore::NONE;

	EWeaponAbilityBullet WeaponAbilityBullet = EWeaponAbilityBullet::NONE;
};