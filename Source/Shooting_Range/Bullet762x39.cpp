#include "Bullet762x39.h"

ABullet762x39::ABullet762x39()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BULLET762X39(TEXT("/Game/FPS_Weapon_Bundle/Weapons/Meshes/Ammunition/SM_Shell_762x39.SM_Shell_762x39"));
	if (BULLET762X39.Succeeded())
	{
		Shell->SetStaticMesh(BULLET762X39.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> EMPTYBULLET762X39(TEXT("/Game/FPS_Weapon_Bundle/Weapons/Meshes/Ammunition/SM_Shell_762x39_Empty.SM_Shell_762x39_Empty"));
	if (EMPTYBULLET762X39.Succeeded())
	{
		Shell->SetStaticMesh(EMPTYBULLET762X39.Object);
	}

	Damage = 7.62f;
	Speed = 76.2f;
}