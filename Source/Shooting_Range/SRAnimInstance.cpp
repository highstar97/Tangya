#include "SRAnimInstance.h"

USRAnimInstance::USRAnimInstance()
{
	bIsAttacking = false;
	bZoomIn = false;
	bCanJump = true;
	bCrouching = false;
	Speed = 0.0f;
	Direction = 0.0f;
	UpDown = 0.0f;
	LeftRight = 0.0f;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("/Game/AnimStarterPack/Fire_Rifle_Hip_Montage.Fire_Rifle_Hip_Montage"));
	if (ATTACK_MONTAGE.Succeeded())
	{
		AttackMontage = ATTACK_MONTAGE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> IRONSIGHT_ATTACKMONTAGE(TEXT("/Game/AnimStarterPack/Fire_Rifle_Ironsights_Montage.Fire_Rifle_Ironsights_Montage"));
	if (IRONSIGHT_ATTACKMONTAGE.Succeeded())
	{
		Ironsight_AttackMontage = IRONSIGHT_ATTACKMONTAGE.Object;
	}
}

void USRAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		Speed = sqrt(pow(Pawn->GetVelocity().X, 2) + pow(Pawn->GetVelocity().Y, 2));
		Direction = CalculateDirection(Pawn->GetVelocity(), Pawn->GetActorRotation());
		FVector EulerVector = Pawn->GetControlRotation().Euler();
		UpDown = EulerVector.Y <= 45.0f ? EulerVector.Y : EulerVector.Y - 360.0f;
		if (Speed > 0.0f)
		{
			LastRotationYaw = Pawn->GetControlRotation().Euler().Z;
		}
		if (LastRotationYaw < 180.0f)
		{
			LeftRight = EulerVector.Z <= LastRotationYaw + 180.0f ? EulerVector.Z - LastRotationYaw : EulerVector.Z - EulerVector.Z - 360.0f;
		}
		else
		{
			LeftRight = EulerVector.Z >= LastRotationYaw - 180.0f ? EulerVector.Z - LastRotationYaw : EulerVector.Z - EulerVector.Z + 360.0f;
		}
	}
}

void USRAnimInstance::SetbIsAttacking(bool boolean)
{
	bIsAttacking = boolean;
}

void USRAnimInstance::SetbCanJump(bool boolean)
{
	bCanJump = boolean;
}

void USRAnimInstance::SetbCrouching(bool boolean)
{
	bCrouching = boolean;
}

void USRAnimInstance::ChangebZoomIn()
{
	bZoomIn = !bZoomIn;
}

void USRAnimInstance::PlayAttackMontage()
{
	bIsAttacking = true;
	if (bZoomIn)
	{
		Montage_Play(Ironsight_AttackMontage);
	}
	else
	{
		Montage_Play(AttackMontage);
	}
}