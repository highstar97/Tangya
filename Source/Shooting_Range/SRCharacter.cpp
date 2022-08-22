#include "SRCharacter.h"
#include "Gameframework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ASRCharacter::ASRCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	// Skeletal Mesh 추가

	// Anim Blueprint 생성 후, AnimInstance에 연결
}

void ASRCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ASRCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ASRCharacter::MoveRight);
	
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ASRCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("TurnRight"), this, &ASRCharacter::TurnRight);
}

void ASRCharacter::MoveForward(float NewAxisValue)
{
	if ((nullptr != Controller) && (NewAxisValue != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, NewAxisValue);
	}
}

void ASRCharacter::MoveRight(float NewAxisValue)
{
	if ((Controller != nullptr) && (NewAxisValue != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, NewAxisValue);
	}
}

void ASRCharacter::LookUp(float NewAxisValue)
{
	if ((nullptr != Controller) && (NewAxisValue != 0.0f))
	{
		APlayerController* const PlayerController = CastChecked<APlayerController>(Controller);
		PlayerController->AddPitchInput(NewAxisValue);
	}
}

void ASRCharacter::TurnRight(float NewAxisValue)
{
	if ((nullptr != Controller) && (NewAxisValue != 0.0f))
	{
		APlayerController* const PlayerController = CastChecked<APlayerController>(Controller);
		PlayerController->AddYawInput(NewAxisValue);
	}
}

