#pragma once

#include "GameFramework/SaveGame.h"
#include "SRSaveGame.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FSRRankData
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FString Name;

	UPROPERTY()
	int32 Score;

	UPROPERTY()
	FString Comment;

	friend bool operator==(const FSRRankData& Lhs, const FSRRankData& Rhs)
	{
		return Lhs.Name == Rhs.Name && Lhs.Score == Rhs.Score && Lhs.Comment == Rhs.Comment;
	}
};

USTRUCT(Atomic, BlueprintType)
struct FSRSettingData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	float Sound;

	UPROPERTY(BlueprintReadOnly)
	float Light;

	UPROPERTY(BlueprintReadOnly)
	float MouseSensitivity;
};

UCLASS()
class SHOOTING_RANGE_API USRSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	USRSaveGame();

	void AddRankData(FSRRankData RankData);

	void UpdateSettingData(float NewSound, float NewLight, float NewMouseSensitivity);

	int32 CheckRank(FSRRankData TempData);

	TArray<FSRRankData> GetRankArray() { return RankArray; }

	UFUNCTION(BlueprintCallable)
	FSRSettingData GetSettingData() { return SettingData; }

private:
	UPROPERTY()
	TArray<FSRRankData> RankArray;

	UPROPERTY()
	FSRSettingData SettingData;
};
