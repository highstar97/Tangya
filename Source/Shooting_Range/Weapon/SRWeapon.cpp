#include "SRWeapon.h"
#include "SRBullet.h"
#include "SREmptyBullet.h"

ASRWeapon::ASRWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponClass = ASRWeapon::StaticClass();

	Image = nullptr;
	Name = TEXT("Weapon");
	Ability = TEXT("No Ability");

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	SetRootComponent(Mesh);

	Bullet = nullptr;
	EmptyBullet = nullptr;

	WeaponAbilityScore = EWeaponAbilityScore::NONE;
	WeaponAbilityBullet = EWeaponAbilityBullet::NONE;
}

ASRBullet* ASRWeapon::ShootBullet(UWorld* World, FVector MuzzleLocation, FRotator MuzzleRotation, FActorSpawnParameters SpawnParams)
{
	if (World)
	{
		Bullet = World->SpawnActor<ASRBullet>(BulletClass, MuzzleLocation, MuzzleRotation, SpawnParams);
		if (Bullet)
		{
			FVector LaunchDirection = MuzzleRotation.Vector();
			Bullet->FireInDirection(LaunchDirection);
		}
		return Bullet;
	}
	return nullptr;;
}

ASREmptyBullet* ASRWeapon::ShootEmptyBullet(UWorld* World, FVector ShellEjectLocation, FRotator ShellEjectRotation, FActorSpawnParameters SpawnParams)
{
	if (World)
	{
		EmptyBullet = World->SpawnActor<ASREmptyBullet>(EmptyBulletClass, ShellEjectLocation, ShellEjectRotation, SpawnParams);
		if (EmptyBullet)
		{
			FVector LaunchDirection = ShellEjectRotation.Vector();
			EmptyBullet->BounceOff(LaunchDirection);
		}
		return EmptyBullet;
	}
	return nullptr;
}

void ASRWeapon::BeginPlay()
{
	Super::BeginPlay();
}