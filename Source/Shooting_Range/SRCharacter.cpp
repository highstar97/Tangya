#include "SRCharacter.h"
#include "SRPlayerController.h"
#include "SRAnimInstance.h"
#include "SRBullet.h"
#include "Bullet762x39.h"
#include "SREmptyBullet.h"
#include "EmptyBullet762x39.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
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

	SetControlMode(EControlView::ThirdPersonView);

	// Equipt Weapon
	FName WeaponSocket(TEXT("hand_rSocket"));
	if (GetMesh()->DoesSocketExist(WeaponSocket))
	{
		Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_WEAPON(TEXT("/Game/FPS_Weapon_Bundle/Weapons/Meshes/Ka47/SK_KA47_X.SK_KA47_X"));
		if (SK_WEAPON.Succeeded())
		{
			Weapon->SetSkeletalMesh(SK_WEAPON.Object);
		}
		Weapon->SetupAttachment(GetMesh(), WeaponSocket);
	}

	AimingAngle = 0.0f;
	
	// attach ADSCamera to weapon
	FName ADSCameraSocket(TEXT("ADS_Socket"));
	if (Weapon->DoesSocketExist(ADSCameraSocket))
	{
		ADSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ADSCAMERA"));
		
		ADSCamera->SetupAttachment(Weapon, ADSCameraSocket);
		ADSCamera->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(90.0f, 90.0f, 0.0f));
	}

	// Sound
	static ConstructorHelpers::FObjectFinder<USoundWave> ATTACKSOUND(TEXT("/Game/Indoor_Shooting_Range/Map/FirstPerson/Audio/FirstPersonTemplateWeaponFire02.FirstPersonTemplateWeaponFire02"));
	if (ATTACKSOUND.Succeeded())
	{
		AttackSound = ATTACKSOUND.Object;
	}
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
	PlayerInputComponent->BindAction(TEXT("ChangeControlView"), EInputEvent::IE_Pressed, this, &ASRCharacter::ChangeControlView);
	PlayerInputComponent->BindAction(TEXT("ZoomIn"), EInputEvent::IE_Pressed, this, &ASRCharacter::ZoomIn);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &ASRCharacter::Fire);
	PlayerInputComponent->BindAction(TEXT("Click Up"), EInputEvent::IE_Pressed, this, &ASRCharacter::ClickUp);
	PlayerInputComponent->BindAction(TEXT("Click Down"), EInputEvent::IE_Pressed, this, &ASRCharacter::ClickDown);
	PlayerInputComponent->BindAction(TEXT("Stop"), EInputEvent::IE_Pressed, this, &ASRCharacter::StopAnim);
	PlayerInputComponent->BindAction(TEXT("Stop"), EInputEvent::IE_Released, this, &ASRCharacter::UnStopAnim);
	
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

	SRAnim->OnMontageEnded.AddDynamic(this, &ASRCharacter::OnAttackMontageEnded);
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
	if (SRAnim->GetbCrouching())
	{
		SRAnim->SetbCrouching(false);
		ChangeMovementState(EMovementState::Idle);
	}
	else
	{
		SRAnim->SetbCrouching(true);
		ChangeMovementState(EMovementState::Crouching);
	}
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

void ASRCharacter::StopAnim()
{
	if (SRAnim)
	{
		SRAnim->SetbStop(true);
	}
}

void ASRCharacter::UnStopAnim()
{
	if (SRAnim)
	{
		SRAnim->SetbStop(false);
	}
}

void ASRCharacter::ChangeControlView()
{
	switch (CurrentControlView)
	{
	case EControlView::FirstPersonView:
	{
		SetControlMode(EControlView::ThirdPersonView);
		break;
	}
	case EControlView::ThirdPersonView:
	{
		SetControlMode(EControlView::FirstPersonView);
		break;
	}
	}
}

void ASRCharacter::SetControlMode(EControlView NewControlMode)
{
	CurrentControlView = NewControlMode;

	switch (CurrentControlView)
	{
	case EControlView::FirstPersonView:
	{
		SpringArm->TargetArmLength = -30.0f;
		SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
		break;
	}
	case EControlView::ThirdPersonView:
	{
		SpringArm->TargetArmLength = 250.0f;
		SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
		break;
	}
	}
}

void ASRCharacter::ChangeMovementState(EMovementState NewState)
{
	switch (NewState)
	{
	case(EMovementState::Idle):
	{
		FVector NewCapsuleLocation = GetActorLocation();
		NewCapsuleLocation.Z = 303.650208f;
		GetCapsuleComponent()->SetCapsuleHalfHeight(100.0f);
		GetCapsuleComponent()->SetRelativeLocation(NewCapsuleLocation);

		FVector NewMeshLocation = GetMesh()->GetRelativeLocation();
		NewMeshLocation.Z = -100.0f;
		GetMesh()->SetRelativeLocation(NewMeshLocation);

		SpringArm->TargetArmLength = 250.0f;
		SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
		Camera->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

		GetCharacterMovement()->MaxWalkSpeed = 500.0f;
		break;
	}
	case(EMovementState::Crouching):
	{
		FVector NewCapsuleLocation = GetActorLocation();
		NewCapsuleLocation.Z = 263.650208f;
		GetCapsuleComponent()->SetCapsuleHalfHeight(60.0f);
		GetCapsuleComponent()->SetRelativeLocation(NewCapsuleLocation);

		FVector NewMeshLocation = GetMesh()->GetRelativeLocation();
		NewMeshLocation.Z = -60.0f;
		GetMesh()->SetRelativeLocation(NewMeshLocation);

		SpringArm->TargetArmLength = 180.0f;
		Camera->SetRelativeLocation(FVector(0.0f, 0.0f, -25.0f));

		GetCharacterMovement()->MaxWalkSpeed = 250.0f;
		break;
	}
	}
}

void ASRCharacter::ZoomIn()
{
	if (nullptr != SRAnim)
	{
		SRAnim->ChangebZoomIn();
		if (SRAnim->GetbZoomIn())
		{
			Camera->Deactivate();
			ADSCamera->Activate();
		}
		else
		{
			Camera->Activate();
			ADSCamera->Deactivate();
		}
	}
	
}

void ASRCharacter::ClickUp()
{
	if (0 <= AimingAngle && AimingAngle < 45)
	{
		AimingAngle += 1;
		UE_LOG(LogTemp, Warning, TEXT("1 Click Up, Now : %d"), AimingAngle);
	}
}

void ASRCharacter::ClickDown()
{
	if (0 < AimingAngle && AimingAngle <= 45)
	{
		AimingAngle -= 1;
		UE_LOG(LogTemp, Warning, TEXT("1 Click Down, Now : %d"), AimingAngle);
	}
}

// Shoot Bullet on 70cm forward from Camera Location
void ASRCharacter::Fire()
{
	ASRPlayerController* SRPlayerController = Cast<ASRPlayerController>(GetController());
	if (nullptr == SRPlayerController)
	{
		return;
	}
	if (SRAnim->GetbCrouching())
	{
		//UE_LOG(LogAnimation, Warning, TEXT("Can't Fire Bullet on Crouching State!"));
		return;
	}
	if (!SRAnim->GetbIsAttacking())
	{
		FVector CameraLocation;
		FRotator CameraRotation;
		FVector MuzzleLocation;
		FRotator MuzzleRotation;

		if (!SRAnim->GetbZoomIn())
		{
			SRAnim->SetbIsAttacking(true);
			CameraLocation = GetActorLocation() + SpringArm->GetRelativeLocation() + Camera->GetRelativeLocation();
			CameraRotation = GetViewRotation();

			MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(FVector(70.0f, 0.0f, 0.0f));
			MuzzleRotation = CameraRotation;
		}
		else
		{
			SRAnim->SetbIsAttacking(true);
			CameraLocation = ADSCamera->GetComponentLocation();
			CameraRotation = ADSCamera->GetComponentRotation();

			MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(FVector(70.0f, 0.0f, 0.0f));
			MuzzleRotation = CameraRotation;
		}
		FName ShellEjectSocket(TEXT("ShellEject"));
		FVector ShellEjectLocation = Weapon->GetSocketLocation(ShellEjectSocket);
		FRotator ShellEjectRotation = CameraRotation;

		UWorld* World = GetWorld();
		if (World)
		{
			// Bullet
			MuzzleRotation.Pitch += AimingAngle;
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			ABullet762x39* Bullet = World->SpawnActor<ABullet762x39>(ABullet762x39::StaticClass(), MuzzleLocation, MuzzleRotation, SpawnParams);
			Bullet->SetActorScale3D(FVector(5.0f, 5.0f, 5.0f));
			if (Bullet)
			{
				FVector LaunchDirection = MuzzleRotation.Vector();
				Bullet->FireInDirection(LaunchDirection);
			}

			// EmptyBullet
			AEmptyBullet762x39* EmptyBullet = World->SpawnActor<AEmptyBullet762x39>(AEmptyBullet762x39::StaticClass(), ShellEjectLocation, ShellEjectRotation, SpawnParams);
			//EmptyBullet->SetActorScale3D(FVector(10.0f, 10.0f, 10.0f));
			if (EmptyBullet)
			{
				FVector LaunchDirection = ShellEjectRotation.Vector();
				EmptyBullet->BounceOff(LaunchDirection);
			}
		}

		UGameplayStatics::PlaySound2D(World, AttackSound);

		SRAnim->PlayAttackMontage();
		SRPlayerController->SubtractCurrentBullet();
	}
}

void ASRCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (SRAnim->GetbIsAttacking())
	{
		SRAnim->SetbIsAttacking(false);
	}
}