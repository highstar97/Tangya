#include "AR4_X.h"
#include "Bullet762x39.h"
#include "EmptyBullet762x39.h"

AAR4_X::AAR4_X()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_WEAPON(TEXT("/Game/FPS_Weapon_Bundle/Weapons/Meshes/AR4/SK_AR4_X.SK_AR4_X"));
	if (SK_WEAPON.Succeeded())
	{
		Mesh->SetSkeletalMesh(SK_WEAPON.Object);
	}

	Bullet = CreateDefaultSubobject<ABullet762x39>(TEXT("BULLET_7.62"));
	EmptyBullet = CreateDefaultSubobject<AEmptyBullet762x39>(TEXT("EMPTYBULLET_7.62"));
}

USkeletalMeshComponent* AAR4_X::GetMesh()
{
	Super::GetMesh();
	return Mesh;
}

USoundWave* AAR4_X::GetAttackSound()
{
	Super::GetAttackSound();
	return AttackSound;
}

ASRBullet* AAR4_X::ShootBullet(UWorld* World, FVector MuzzleLocation, FRotator MuzzleRotation, FActorSpawnParameters SpawnParams)
{
	Super::ShootBullet(World, MuzzleLocation, MuzzleRotation, SpawnParams);
	if (World)
	{
		Bullet = World->SpawnActor<ABullet762x39>(ABullet762x39::StaticClass(), MuzzleLocation, MuzzleRotation, SpawnParams);
		if (Bullet)
		{
			Bullet->SetActorScale3D(FVector(5.0f, 5.0f, 5.0f));
			FVector LaunchDirection = MuzzleRotation.Vector();
			Bullet->FireInDirection(LaunchDirection);
		}
		return Bullet;
	}
	return nullptr;
}

ASREmptyBullet* AAR4_X::ShootEmptyBullet(UWorld* World, FVector ShellEjectLocation, FRotator ShellEjectRotation, FActorSpawnParameters SpawnParams)
{
	Super::ShootEmptyBullet(World, ShellEjectLocation, ShellEjectRotation, SpawnParams);
	if (World)
	{
		EmptyBullet = World->SpawnActor<AEmptyBullet762x39>(AEmptyBullet762x39::StaticClass(), ShellEjectLocation, ShellEjectRotation, SpawnParams);
		if (EmptyBullet)
		{
			EmptyBullet->SetActorScale3D(FVector(5.0f, 5.0f, 5.0f));
			FVector LaunchDirection = ShellEjectRotation.Vector();
			EmptyBullet->BounceOff(LaunchDirection);
		}
		return EmptyBullet;
	}
	return nullptr;
}
