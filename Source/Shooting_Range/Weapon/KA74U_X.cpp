#include "KA74U_X.h"

AKA74U_X::AKA74U_X()
{
	WeaponClass = AKA74U_X::StaticClass();

	Name = TEXT("KA47U");
	Ability = TEXT("\nTotal Bullet -3, Score per Bullet +2");

	WeaponAbilityScore = EWeaponAbilityScore::ADD2;
	WeaponAbilityBullet = EWeaponAbilityBullet::SUBTRACT3;
}