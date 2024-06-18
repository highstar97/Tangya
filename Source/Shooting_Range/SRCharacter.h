#pragma once

#include "GameFramework/Character.h"
#include "SRCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USRAnimInstance;
class ASRWeapon;

UENUM()
enum class EControlView
{
	FirstPersonView,
	ThirdPersonView,
};

UENUM()
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

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;

public:
	USpringArmComponent* GetSpringArm() const { return SpringArm; }

	UCameraComponent* GetCamera() const { return Camera; }

	UCameraComponent* GetADSCamera() const { return ADSCamera; }

	EControlView GetCurrentControlView() const { return CurrentControlView; }

	USRAnimInstance* GetSRAnim() const { return SRAnim; }

	int32 GetAimingAngle() const { return AimingAngle; }

	ASRWeapon* GetCurrentWeapon() const { return CurrentWeapon; }

private:
// Movement
	void MoveForward(float NewAxisValue);

	void MoveRight(float NewAxisValue);

	void LookUp(float NewAxisValue);

	void TurnRight(float NewAxisValue);

	void Jump();

	void Crouch();

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

private:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	UCameraComponent* ADSCamera;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	EControlView CurrentControlView;

	UPROPERTY(VisibleAnywhere, Category = "Animation")
	USRAnimInstance* SRAnim;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	int32 AimingAngle;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	ASRWeapon* CurrentWeapon;
};