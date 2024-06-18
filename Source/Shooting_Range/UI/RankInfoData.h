#pragma once

#include "UObject/NoExportTypes.h"
#include "RankInfoData.generated.h"

UCLASS()
class SHOOTING_RANGE_API URankInfoData : public UObject
{
	GENERATED_BODY()

public:
	URankInfoData();

	void SetRank(const int32 NewRank) { Rank = NewRank; }
	int32 GetRank() const { return Rank; }

	void SetName(const FString& NewName) { Name = NewName; }
	FString GetName() const { return Name; }

	void SetScore(const int32 NewScore) { Score = NewScore; }
	int32 GetScore() const { return Score; }

	void SetComment(const FString& NewComment) { Comment = NewComment; }
	FString GetComment() const { return Comment; }

private:
	UPROPERTY()
	int32 Rank;

	UPROPERTY()
	FString Name;

	UPROPERTY()
	int32 Score;

	UPROPERTY()
	FString Comment;
};
