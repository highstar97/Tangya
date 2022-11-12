#pragma once

#include "UObject/NoExportTypes.h"
#include "WeaponInfoData.generated.h"

UCLASS()
class SHOOTING_RANGE_API UWeaponInfoData : public UObject
{
	GENERATED_BODY()

public:
	UWeaponInfoData();

	UTexture2D* GetImage() { return Image; }
	void SetImage(UTexture2D* NewImage) { Image = NewImage; }
	
	FString GetName() { return Name; }
	void SetName(FString NewName) { Name = NewName; }

	FString GetAbility() { return Ability; }
	void SetAbility(FString NewAbilty) { Ability = NewAbilty; }

private:
	UPROPERTY(EditAnywhere)
	UTexture2D* Image;

	UPROPERTY(EditAnywhere)
	FString Name;

	UPROPERTY(EditAnywhere)
	FString Ability;
};
