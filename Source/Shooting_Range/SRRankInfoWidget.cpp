#include "SRRankInfoWidget.h"
#include "RankInfoData.h"
#include "SRSaveGame.h"
#include "Components/TextBlock.h"

void USRRankInfoWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	URankInfoData* RankInfoData = Cast<URankInfoData>(ListItemObject);

	if (Text_Rank)
	{
		Text_Rank->SetText(FText::FromString(FString::FromInt(RankInfoData->GetRank())));
	}
	if (Text_Name)
	{
		Text_Name->SetText(FText::FromString(RankInfoData->GetName()));
	}
	if (Text_Score)
	{
		Text_Score->SetText(FText::FromString(FString::FromInt(RankInfoData->GetScore())));
	}
	if (Text_Comment)
	{
		Text_Comment->SetText(FText::FromString(RankInfoData->GetComment()));
	}
}
