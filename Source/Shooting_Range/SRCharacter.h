#pragma once

#include "GameFramework/Character.h"
#include "SRCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USRAnimInstance;

enum class EControlView
{
	FirstPersonView,
	ThirdPersonView,
};

enum class EMovementState
{
	Idle,
	Crouching,
};

UCLASS()
class SHOOTING_RANGE_API ASRCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASRCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;

private:
	void Jump();
	void Crouch();
	void MoveForward(float NewAxisValue);
	void MoveRight(float NewAxisValue);
	void LookUp(float NewAxisValue);
	void TurnRight(float NewAxisValue);

	void ChangeControlView();
	void SetControlMode(EControlView NewControlView);

	void ChangeMovementState(EMovementState NewState);

	void ZoomIn();

	void ClickUp();
	void ClickDown();

	void Fire();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

public:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;

	EControlView CurrentControlView = EControlView::ThirdPersonView;

	UPROPERTY()
	USRAnimInstance* SRAnim;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	USkeletalMeshComponent* Weapon;

	UPROPERTY(VisibleAnywhere, Category = Sound)
	USoundWave* AttackSound;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	int32 AimingAngle;

	//UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	//float MouseSensitivity = 1.0f;
};
