#pragma once

#include "Animation/AnimInstance.h"
#include "SRAnimInstance.generated.h"

UCLASS()
class SHOOTING_RANGE_API USRAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	USRAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	bool GetbCanJump() { return bCanJump; }
	void SetbCanJump(bool boolean);

	bool GetbCrouching() { return bCrouching; }
	void SetbCrouching(bool boolean);

	void ChangebJoomIn();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character, Meta = (AllowPrivateAccess = true))
	bool bZoomIn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character, Meta = (AllowPrivateAccess = true))
	bool bCanJump;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	bool bCrouching;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	float Direction;
};