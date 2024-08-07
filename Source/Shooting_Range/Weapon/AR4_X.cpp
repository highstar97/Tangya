#include "AR4_X.h"

AAR4_X::AAR4_X()
{
	WeaponClass = AAR4_X::StaticClass();

	Name = TEXT("AR4");
	Ability = TEXT("\nTotal Bullet + 3");

	WeaponAbilityScore = EWeaponAbilityScore::NONE;
	WeaponAbilityBullet = EWeaponAbilityBullet::ADD3;
}