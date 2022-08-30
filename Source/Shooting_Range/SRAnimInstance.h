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

	void SetEnableJump(bool boolean);

	bool GetCrouching() { return Crouching; }
	void SetCrouching(bool boolean);

	bool GetJumping() { return Jumping; }

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character, Meta = (AllowPrivateAccess = true))
	bool EnableJump;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character, Meta = (AllowPrivateAccess = true))
	bool Jumping;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	bool Crouching;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	float Direction;
};
