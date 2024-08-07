#include "SRSelectWeaponWidget.h"

#include "Components/TileView.h"

#include "WeaponInfoData.h"
#include "SRWeapon.h"

void USRSelectWeaponWidget::UpdateWidget()
{
	int32 NumOfWeapon = 3;
	if (WeaponArray.Num() == 0) return;

	if (Tile_WeaponInfo->GetNumItems() == NumOfWeapon) return;

	for (int32 i = 0; i < NumOfWeapon; ++i)
	{
		ASRWeapon* Weapon = nullptr;
		Weapon = GetWorld()->SpawnActor<ASRWeapon>(WeaponArray[i]);
		
		UWeaponInfoData* WeaponInfoData = NewObject<UWeaponInfoData>(this, UWeaponInfoData::StaticClass());
		WeaponInfoData->SetImage(Weapon->GetImage());
		WeaponInfoData->SetName(Weapon->GetName());
		WeaponInfoData->SetAbility(Weapon->GetAbility());

		Tile_WeaponInfo->AddItem(WeaponInfoData);
	}
}