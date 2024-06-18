#include "SRWeaponInfoWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "WeaponInfoData.h"

void USRWeaponInfoWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UWeaponInfoData* WeaponInfoData = Cast<UWeaponInfoData>(ListItemObject);

	Name = WeaponInfoData->GetName();

	if (Image_Weapon)
	{
		Image_Weapon->SetBrushFromTexture(WeaponInfoData->GetImage());
	}
	if (Text_WeaponInfo)
	{
		FString WeaponInfo =  TEXT("Gun Name : ") + WeaponInfoData->GetName() + TEXT("\nAbility : ") + WeaponInfoData->GetAbility();
		Text_WeaponInfo->SetText(FText::FromString(WeaponInfo));
	}
}