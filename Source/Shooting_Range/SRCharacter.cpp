#include "SRCharacter.h"
#include "SRAnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Gameframework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ASRCharacter::ASRCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->InitCapsuleSize(45.0f, 100.0f);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bDoCollisionTest = true;

	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_MANNEQUIN(TEXT("/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin"));
	if (SK_MANNEQUIN.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_MANNEQUIN.Object);
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> THIRDPERSON_ANIM(TEXT("/Game/Blueprints/ThirdPersonAnimBlueprint.ThirdPersonAnimBlueprint_C"));
	if (THIRDPERSON_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(THIRDPERSON_ANIM.Class);
	}

	SetControlMode(EControlMode::ThirdPersonView);
}

void ASRCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed ,this, &ASRCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Pressed, this, &ASRCharacter::Crouch);
	PlayerInputComponent->BindAction(TEXT("ViewChange"), EInputEvent::IE_Pressed, this, &ASRCharacter::ViewChange);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ASRCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ASRCharacter::MoveRight);
	
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ASRCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("TurnRight"), this, &ASRCharacter::TurnRight);
}

void ASRCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SRAnim = Cast<USRAnimInstance>(GetMesh()->GetAnimInstance());
	if (nullptr == SRAnim)
	{
		UE_LOG(LogTemp, Error, TEXT("SRAnim is nullptr"));
	}
}

void ASRCharacter::Jump()
{
	if (true == SRAnim->GetbCanJump() && false == SRAnim->GetbCrouching())
	{
		SRAnim->SetbCanJump(false);
		bPressedJump = true;
		JumpKeyHoldTime = 0.0f;
	}
}

void ASRCharacter::Crouch()
{
	SRAnim->GetbCrouching() == true ? SRAnim->SetbCrouching(false) : SRAnim->SetbCrouching(true);
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

void ASRCharacter::ViewChange()
{
	switch (CurrentControlMode)
	{
	case EControlMode::FirstPersonView:
	{
		SetControlMode(EControlMode::ThirdPersonView);
		break;
	}
	case EControlMode::ThirdPersonView:
	{
		SetControlMode(EControlMode::FirstPersonView);
		break;
	}
	}
}

void ASRCharacter::SetControlMode(EControlMode NewControlMode)
{
	CurrentControlMode = NewControlMode;

	switch (CurrentControlMode)
	{
	case EControlMode::FirstPersonView:
	{
		SpringArm->TargetArmLength = -30.0f;
		SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
		break;
	}
	case EControlMode::ThirdPersonView:
	{
		SpringArm->TargetArmLength = 250.0f;
		SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));

		if (nullptr != Controller)		// 처음 시작 시 적용 안됨 -> 나중에 함수로 빼서 해결 필요해 보임
		{
			APlayerController* const PlayerController = CastChecked<APlayerController>(Controller);
			PlayerController->PlayerCameraManager->ViewPitchMin = -45.0f;
			PlayerController->PlayerCameraManager->ViewPitchMax = 45.0f;
		}
		break;
	}
	}
}