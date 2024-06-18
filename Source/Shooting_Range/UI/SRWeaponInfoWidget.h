#pragma once

#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "SRWeaponInfoWidget.generated.h"

class UButton;
class UImage;
class UTextBlock;

UCLASS()
class SHOOTING_RANGE_API USRWeaponInfoWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

public:
	UPROPERTY(BlueprintReadWrite)
	FString Name;

private:
	UPROPERTY(meta = (BindWidget))
	UButton* Button_WeaponInfo;

	UPROPERTY(meta = (BindWidget))
	UImage* Image_Weapon;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_WeaponInfo;
};