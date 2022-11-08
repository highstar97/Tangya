#pragma once

#include "Blueprint/UserWidget.h"
#include "SRRankingWidget.generated.h"

class USRRankInfoWidget;
class UListView;

UCLASS()
class SHOOTING_RANGE_API USRRankingWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void UpdateWidget();

private:
	UPROPERTY(meta = (BindWidget))
	UListView* List_Rank;
};