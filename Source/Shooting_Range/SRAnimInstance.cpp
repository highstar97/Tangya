#include "SRAnimInstance.h"

USRAnimInstance::USRAnimInstance()
{
	bIsAttacking = false;
	bZoomIn = false;
	bCanJump = true;
	bCrouching = false;
	Speed = 0.0f;
	Direction = 0.0f;

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