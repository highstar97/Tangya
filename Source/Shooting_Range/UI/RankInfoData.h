#pragma once

#include "UObject/NoExportTypes.h"
#include "RankInfoData.generated.h"

UCLASS()
class SHOOTING_RANGE_API URankInfoData : public UObject
{
	GENERATED_BODY()

public:
	URankInfoData();

	void SetRank(int32 NewRank) { Rank = NewRank; }
	int32 GetRank() { return Rank; }

	void SetName(FString NewName) { Name = NewName; }
	FString GetName() { return Name; }

	void SetScore(int32 NewScore) { Score = NewScore; }
	int32 GetScore() { return Score; }

	void SetComment(FString NewComment) { Comment = NewComment; }
	FString GetComment() { return Comment; }

private:
	UPROPERTY(EditAnywhere)
	int32 Rank;

	UPROPERTY(EditAnywhere)
	FString Name;

	UPROPERTY(EditAnywhere)
	int32 Score;

	UPROPERTY(EditAnywhere)
	FString Comment;
};
