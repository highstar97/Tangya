#pragma once

#include "Blueprint/UserWidget.h"
#include "SRSelectWeaponWidget.generated.h"

class UTileView;

UCLASS()
class SHOOTING_RANGE_API USRSelectWeaponWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateWidget();

private:
	UPROPERTY(meta = (BindWidget))
	UTileView* Tile_WeaponInfo;
};