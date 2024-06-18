#include "KA74U_X.h"
#include "Bullet762x39.h"
#include "EmptyBullet762x39.h"

AKA74U_X::AKA74U_X()
{
	WeaponClass = AKA74U_X::StaticClass();

	static ConstructorHelpers::FObjectFinder<UTexture2D> IMAGE_KA74U_X(TEXT("/Game/FPS_Weapon_Bundle/Weapons/Meshes/KA74U/KA47U.KA47U"));
	if (IMAGE_KA74U_X.Succeeded())
	{
		Image = IMAGE_KA74U_X.Object;
	}

	Name = TEXT("KA47U");
	Ability = TEXT("\nTotal Bullet -3, Score per Bullet +2");

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_WEAPON(TEXT("/Game/FPS_Weapon_Bundle/Weapons/Meshes/KA74U/SK_KA74U_X.SK_KA74U_X"));
	if (SK_WEAPON.Succeeded())
	{
		Mesh->SetSkeletalMesh(SK_WEAPON.Object);
	}

	Bullet = CreateDefaultSubobject<ABullet762x39>(TEXT("BULLET_7.62"));
	EmptyBullet = CreateDefaultSubobject<AEmptyBullet762x39>(TEXT("EMPTYBULLET_7.62"));

	WeaponAbilityScore = EWeaponAbilityScore::ADD2;
	WeaponAbilityBullet = EWeaponAbilityBullet::SUBTRACT3;
}

ASRBullet* AKA74U_X::ShootBullet(UWorld* World, FVector MuzzleLocation, FRotator MuzzleRotation, FActorSpawnParameters SpawnParams)
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

ASREmptyBullet* AKA74U_X::ShootEmptyBullet(UWorld* World, FVector ShellEjectLocation, FRotator ShellEjectRotation, FActorSpawnParameters SpawnParams)
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