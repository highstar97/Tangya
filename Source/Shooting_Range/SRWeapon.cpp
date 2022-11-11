#include "SRWeapon.h"
#include "SRBullet.h"
#include "SREmptyBullet.h"
#include "Particles/ParticleSystem.h"

ASRWeapon::ASRWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponClass = ASRWeapon::StaticClass();

	Image = nullptr;
	Name = TEXT("Weapon");
	Ability = TEXT("No Ability");

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	SetRootComponent(Mesh);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> MUZZLEPARTICLE(TEXT("/Game/Particles/P_MuzzleFlash.P_MuzzleFlash"));
	if (MUZZLEPARTICLE.Succeeded())
	{
		MuzzleParticle = MUZZLEPARTICLE.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundWave> ATTACKSOUND(TEXT("/Game/Indoor_Shooting_Range/Map/FirstPerson/Audio/FirstPersonTemplateWeaponFire02.FirstPersonTemplateWeaponFire02"));
	if (ATTACKSOUND.Succeeded())
	{
		AttackSound = ATTACKSOUND.Object;
	}

	Bullet = CreateDefaultSubobject<ASRBullet>(TEXT("BULLET"));
	EmptyBullet = CreateDefaultSubobject<ASREmptyBullet>(TEXT("EMPTYBULLET"));
}

ASRBullet* ASRWeapon::ShootBullet(UWorld* World, FVector MuzzleLocation, FRotator MuzzleRotation, FActorSpawnParameters SpawnParams)
{
	if (World)
	{
		Bullet = World->SpawnActor<ASRBullet>(ASRBullet::StaticClass(), MuzzleLocation, MuzzleRotation, SpawnParams);
		if (Bullet)
		{
			//Bullet->SetActorScale3D(FVector(5.0f, 5.0f, 5.0f));
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
		EmptyBullet = World->SpawnActor<ASREmptyBullet>(ASREmptyBullet::StaticClass(), ShellEjectLocation, ShellEjectRotation, SpawnParams);
		if (EmptyBullet)
		{
			//EmptyBullet->SetActorScale3D(FVector(10.0f, 10.0f, 10.0f));
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