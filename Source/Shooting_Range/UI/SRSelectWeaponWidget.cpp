#include "SRSelectWeaponWidget.h"
#include "WeaponInfoData.h"
#include "SRWeapon.h"
#include "KA47_X.h"
#include "KA74U_X.h"
#include "AR4_X.h"
#include "Components/TileView.h"

void USRSelectWeaponWidget::UpdateWidget()
{
	UWorld* World = GetWorld();
	if (World)
	{
		int32 NumOfWeapon = 3;
		if (Tile_WeaponInfo->GetNumItems() == NumOfWeapon)
		{
			return;
		}
		for (int32 i = 0; i < NumOfWeapon; ++i)
		{
			UWeaponInfoData* WeaponInfoData = NewObject<UWeaponInfoData>(this, UWeaponInfoData::StaticClass());
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
			WeaponInfoData->SetImage(Weapon->GetImage());
			WeaponInfoData->SetName(Weapon->GetName());
			WeaponInfoData->SetAbility(Weapon->GetAbility());
			Tile_WeaponInfo->AddItem(WeaponInfoData);
		}
	}
}