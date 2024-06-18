#include "SRSelectWeaponWidget.h"

#include "Components/TileView.h"

#include "WeaponInfoData.h"
#include "SRWeapon.h"
#include "KA47_X.h"
#include "KA74U_X.h"
#include "AR4_X.h"

void USRSelectWeaponWidget::UpdateWidget()
{
	int32 NumOfWeapon = 3;
	if (Tile_WeaponInfo->GetNumItems() == NumOfWeapon) return;
	
	for (int32 i = 0; i < NumOfWeapon; ++i)
	{
		ASRWeapon* Weapon = nullptr;
		switch (i)
		{
		case(0):
		{
			Weapon = GetWorld()->SpawnActor<ASRWeapon>(AKA47_X::StaticClass());
			break;
		}
		case(1):
		{
			Weapon = GetWorld()->SpawnActor<ASRWeapon>(AKA74U_X::StaticClass());
			break;
		}
		case(2):
		{
			Weapon = GetWorld()->SpawnActor<ASRWeapon>(AAR4_X::StaticClass());
			break;
		}
		}
		
		UWeaponInfoData* WeaponInfoData = NewObject<UWeaponInfoData>(this, UWeaponInfoData::StaticClass());
		WeaponInfoData->SetImage(Weapon->GetImage());
		WeaponInfoData->SetName(Weapon->GetName());
		WeaponInfoData->SetAbility(Weapon->GetAbility());

		Tile_WeaponInfo->AddItem(WeaponInfoData);
	}
}