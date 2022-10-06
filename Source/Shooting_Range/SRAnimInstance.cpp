#include "SRAnimInstance.h"

USRAnimInstance::USRAnimInstance()
{
	bCanJump = true;
	bCrouching = false;
	Speed = 0.0f;
	Direction = 0.0f;
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

void USRAnimInstance::SetbCanJump(bool boolean)
{
	bCanJump = boolean;
}

void USRAnimInstance::SetbCrouching(bool boolean)
{
	bCrouching = boolean;
}
