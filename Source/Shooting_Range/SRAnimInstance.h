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
	
public:
	bool GetbZoomIn() const { return bZoomIn; }
	
	bool GetbIsAttacking() const { return bIsAttacking; }
	void SetbIsAttacking(const bool _bIsAttacking) { bIsAttacking = _bIsAttacking; }

	bool GetbCanJump() const { return bCanJump; }
	void SetbCanJump(const bool _bCanJump) { bCanJump = _bCanJump; }

	bool GetbIsCrouching() const { return bIsCrouching; }
	void SetbIsCrouching(const bool _bIsCrouching) { bIsCrouching = _bIsCrouching; }

	bool GetbIsEquiping() const { return bIsEquiping; }
	void SetbIsEquiping(const bool _bIsEquiping) { bIsEquiping = _bIsEquiping; }

	FRotator GetLastRotation() const { return LastRotation; }

public:
	void ToggleZoomIn() { bZoomIn = !bZoomIn; }

	void PlayAttackMontage();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character, Meta = (AllowPrivateAccess = true))
	bool bIsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character, Meta = (AllowPrivateAccess = true))
	bool bZoomIn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character, Meta = (AllowPrivateAccess = true))
	bool bCanJump;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	bool bIsCrouching;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	bool bIsEquiping;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	float UpDown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	float LeftRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	FRotator LastRotation;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* Ironsight_AttackMontage;
};
