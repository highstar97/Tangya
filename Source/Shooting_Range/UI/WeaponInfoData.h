#pragma once

#include "UObject/NoExportTypes.h"
#include "WeaponInfoData.generated.h"

UCLASS()
class SHOOTING_RANGE_API UWeaponInfoData : public UObject
{
	GENERATED_BODY()

public:
	UWeaponInfoData();

	UTexture2D* GetImage() const { return Image; }

	void SetImage(UTexture2D* NewImage) { Image = NewImage; }
	
	FString GetName() const { return Name; }

	void SetName(const FString& NewName) { Name = NewName; }

	FString GetAbility() const { return Ability; }

	void SetAbility(const FString& NewAbilty) { Ability = NewAbilty; }

private:
	UPROPERTY()
	UTexture2D* Image;

	UPROPERTY()
	FString Name;

	UPROPERTY()
	FString Ability;
};
