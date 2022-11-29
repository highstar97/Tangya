#pragma once

#include "Blueprint/UserWidget.h"
#include "SRCheckRankWidget.generated.h"

class USRSaveGame;
class UEditableTextBox;
class UTextBlock;

UCLASS()
class SHOOTING_RANGE_API USRCheckRankWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void UpdateWidget();

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION(BlueprintCallable)
	void PressedYes();

	UFUNCTION(BlueprintCallable)
	void PressedNo();

private:
	UPROPERTY()
	USRSaveGame* SaveGame;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* ET_Name;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_FinalScore;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_FinalRank;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* ET_Comment;
};