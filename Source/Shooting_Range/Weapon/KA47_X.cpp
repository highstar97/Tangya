#include "KA47_X.h"

AKA47_X::AKA47_X()
{
	WeaponClass = AKA47_X::StaticClass();

	Name = TEXT("KA47");
	Ability = TEXT("\nScore per Bullet +1");

	WeaponAbilityScore = EWeaponAbilityScore::ADD1;
	WeaponAbilityBullet = EWeaponAbilityBullet::NONE;
}