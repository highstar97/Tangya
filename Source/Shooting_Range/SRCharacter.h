#pragma once

#include "GameFramework/Character.h"
#include "SRCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USRAnimInstance;

enum class EControlMode
{
	FirstPersonView,
	ThirdPersonView,
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

	void ViewChange();
	void SetControlMode(EControlMode NewControlMode);

public:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;

	EControlMode CurrentControlMode = EControlMode::ThirdPersonView;

	UPROPERTY()
	USRAnimInstance* SRAnim;
};
