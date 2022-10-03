#pragma once

#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

class UTextBlock;

UCLASS()
class SHOOTING_RANGE_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindWeaponState();
	void BindPlayerState();

protected:
	void NativeConstruct() override;
	void UpdateWeaponState();
	void UpdatePlayerState();

private:
	//TWeakObjectPtr<UWeaponState>
	//TWeakObjectPtr<UPlayerState>

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Score;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* HighScore;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrentBullets;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TotalBullets;
};