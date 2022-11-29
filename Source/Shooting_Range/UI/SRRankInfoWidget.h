#pragma once

#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "SRRankInfoWidget.generated.h"

struct FSRRankData;
class UTextBlock;

UCLASS()
class SHOOTING_RANGE_API USRRankInfoWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Rank;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Name;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Score;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Comment;
};