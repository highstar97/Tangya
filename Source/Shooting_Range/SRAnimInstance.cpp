#include "SRAnimInstance.h"

USRAnimInstance::USRAnimInstance()
{
	EnableJump = true;
	Jumping = false;
	Crouching = false;
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

void USRAnimInstance::SetEnableJump(bool boolean)
{
	EnableJump = boolean;
	Jumping = boolean;
}

void USRAnimInstance::SetCrouching(bool boolean)
{
	Crouching = boolean;
}
