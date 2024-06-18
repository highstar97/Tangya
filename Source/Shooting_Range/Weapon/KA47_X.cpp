#include "KA47_X.h"
#include "Bullet762x39.h"
#include "EmptyBullet762x39.h"

AKA47_X::AKA47_X()
{
	WeaponClass = AKA47_X::StaticClass();

	static ConstructorHelpers::FObjectFinder<UTexture2D> IMAGE_KA47_X(TEXT("/Game/FPS_Weapon_Bundle/Weapons/Meshes/Ka47/KA47.KA47"));
	if (IMAGE_KA47_X.Succeeded())
	{
		Image = IMAGE_KA47_X.Object;
	}

	Name = TEXT("KA47");
	Ability = TEXT("\nScore per Bullet +1");

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_WEAPON(TEXT("/Game/FPS_Weapon_Bundle/Weapons/Meshes/Ka47/SK_KA47_X.SK_KA47_X"));
	if (SK_WEAPON.Succeeded())
	{
		Mesh->SetSkeletalMesh(SK_WEAPON.Object);
	}

	Bullet = CreateDefaultSubobject<ABullet762x39>(TEXT("BULLET_7.62"));
	EmptyBullet = CreateDefaultSubobject<AEmptyBullet762x39>(TEXT("EMPTYBULLET_7.62"));

	WeaponAbilityScore = EWeaponAbilityScore::ADD1;
	WeaponAbilityBullet = EWeaponAbilityBullet::NONE;
}

ASRBullet* AKA47_X::ShootBullet(UWorld* World, FVector MuzzleLocation, FRotator MuzzleRotation, FActorSpawnParameters SpawnParams)
{
	if (World)
	{
		Bullet = World->SpawnActor<ABullet762x39>(ABullet762x39::StaticClass(), MuzzleLocation, MuzzleRotation, SpawnParams);
		if (Bullet)
		{
			FVector LaunchDirection = MuzzleRotation.Vector();
			Bullet->FireInDirection(LaunchDirection);
		}
		return Bullet;
	}
	return nullptr;
}

ASREmptyBullet* AKA47_X::ShootEmptyBullet(UWorld* World, FVector ShellEjectLocation, FRotator ShellEjectRotation, FActorSpawnParameters SpawnParams)
{
	if (World)
	{
		EmptyBullet = World->SpawnActor<AEmptyBullet762x39>(AEmptyBullet762x39::StaticClass(), ShellEjectLocation, ShellEjectRotation, SpawnParams);
		if (EmptyBullet)
		{
			FVector LaunchDirection = ShellEjectRotation.Vector();
			EmptyBullet->BounceOff(LaunchDirection);
		}
		return EmptyBullet;
	}
	return nullptr;
}