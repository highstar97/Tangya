#pragma once

#include "GameFramework/Character.h"
#include "SRCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USRAnimInstance;
class ASRWeapon;

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

	UFUNCTION(BlueprintCallable)
	void EquipWeapon(ASRWeapon* NewWeapon);

	void Fire();
	void Gauging();
	void ApplyBulletAccuracy(float Gauge, FRotator& FireRotation);

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

public:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* ADSCamera;

	EControlView CurrentControlView = EControlView::ThirdPersonView;

	UPROPERTY()
	USRAnimInstance* SRAnim;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	ASRWeapon* Weapon;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	int32 AimingAngle;
};
