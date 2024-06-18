#include "SRCharacter.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Gameframework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "SRPlayerState.h"
#include "SRPlayerController.h"
#include "SRAnimInstance.h"
#include "SRWeapon.h"
#include "KA47_X.h"
#include "AR4_X.h"
#include "KA74U_X.h"

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
	CurrentWeapon = CreateDefaultSubobject<ASRWeapon>(TEXT("WEAPON"));
	ADSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ADSCAMERA"));

	AimingAngle = 0.0f;
}

void ASRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ASRCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Pressed, this, &ASRCharacter::Crouch);
	PlayerInputComponent->BindAction(TEXT("ChangeControlView"), EInputEvent::IE_Pressed, this, &ASRCharacter::ChangeControlView);
	PlayerInputComponent->BindAction(TEXT("ZoomIn"), EInputEvent::IE_Pressed, this, &ASRCharacter::ZoomIn);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Released, this, &ASRCharacter::Fire);
	PlayerInputComponent->BindAction(TEXT("Gauging"), EInputEvent::IE_Pressed, this, &ASRCharacter::Gauging);
	PlayerInputComponent->BindAction(TEXT("Click Up"), EInputEvent::IE_Pressed, this, &ASRCharacter::ClickUp);
	PlayerInputComponent->BindAction(TEXT("Click Down"), EInputEvent::IE_Pressed, this, &ASRCharacter::ClickDown);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ASRCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ASRCharacter::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ASRCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("TurnRight"), this, &ASRCharacter::TurnRight);
}

void ASRCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	SRAnim = Cast<USRAnimInstance>(GetMesh()->GetAnimInstance());
	if (!ensure(SRAnim != nullptr)) return;

	SRAnim->OnMontageEnded.AddDynamic(this, &ASRCharacter::OnAttackMontageEnded);
}

void ASRCharacter::BeginPlay()
{
	Super::BeginPlay();

	ASRPlayerState* SRPlayerState = GetPlayerState<ASRPlayerState>();
	if (!ensure(SRPlayerState != nullptr)) return;

	const int32 BasicNumOfBullets = 10;
	SRPlayerState->SetNumOfTotalBullets(BasicNumOfBullets);
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

void ASRCharacter::Jump()
{
	// The character cannot jump while crouching
	if (true == SRAnim->GetbCanJump() && false == SRAnim->GetbIsCrouching())
	{
		SRAnim->SetbCanJump(false);
		bPressedJump = true;
		JumpKeyHoldTime = 0.0f;
	}
}

void ASRCharacter::Crouch()
{
	if (SRAnim->GetbIsCrouching())
	{
		SRAnim->SetbIsCrouching(false);
		ChangeMovementState(EMovementState::Idle);
	}
	else
	{
		SRAnim->SetbIsCrouching(true);
		ChangeMovementState(EMovementState::Crouching);
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

// Depending on the movement state, the collision judgment and max walking speed are different.
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

// Depending on whether Zoom In or not, the camera used is different
void ASRCharacter::ZoomIn()
{
	if (nullptr != SRAnim)
	{
		SRAnim->ToggleZoomIn();
		if (SRAnim->GetbIsEquiping())
		{
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
}

// Function for zero point adjustment
void ASRCharacter::ClickUp()
{
	if (SRAnim->GetbIsEquiping())
	{
		if (0 <= AimingAngle && AimingAngle < 45)
		{
			AimingAngle += 1;
			UE_LOG(LogTemp, Warning, TEXT("1 Click Up, Now : %d"), AimingAngle);
		}
	}
}

void ASRCharacter::ClickDown()
{
	if (SRAnim->GetbIsEquiping())
	{
		if (0 < AimingAngle && AimingAngle <= 45)
		{
			AimingAngle -= 1;
			UE_LOG(LogTemp, Warning, TEXT("1 Click Down, Now : %d"), AimingAngle);
		}
	}
}

void ASRCharacter::EquipWeapon(ASRWeapon* NewWeapon)
{
	if (!ensure(NewWeapon != nullptr)) return;

	if (IsValid(CurrentWeapon))
	{
		CurrentWeapon->Destroy();
	}

	CurrentWeapon = NewWeapon;

	FName WeaponSocket(TEXT("hand_rSocket"));
	if (GetMesh()->DoesSocketExist(WeaponSocket))
	{
		CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
	}

	FName ADSCameraSocket(TEXT("ADS_Socket"));
	if (CurrentWeapon->GetMesh()->DoesSocketExist(ADSCameraSocket))
	{
		ADSCamera->AttachToComponent(CurrentWeapon->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, ADSCameraSocket);
		ADSCamera->SetRelativeRotation(FRotator(90.0f, 0.0f, -90.0f));
		ADSCamera->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	}

	ASRPlayerController* SRPlayerController = Cast<ASRPlayerController>(GetController());
	if (SRPlayerController)
	{
		SRPlayerController->ToggleSelectWeaponWidget(false);
		if (!SRAnim->GetbIsEquiping())
		{
			SRPlayerController->ToggleHUDWidget(true);
			SRPlayerController->ToggleHuddyWidget(true);
		}
	}

	SRPlayerController->AddBonusBulletsByAbility(CurrentWeapon->GetWeaponAbilityBullet());
	SRAnim->SetbIsEquiping(true);
}

/* 
Depending on whether you zoom in or not, the location where the bullet is fired is different.
In the case of zoom out, fire from 70cm in front of the Main camera.
In the case of zoom in, fire from 70cm in front of the camera on the gun(ADSC Camera).
*/
void ASRCharacter::Fire()
{
	ASRPlayerController* SRPlayerController = Cast<ASRPlayerController>(GetController());
	if (nullptr == SRPlayerController)
	{
		return;
	}
	if (SRAnim->GetbIsCrouching() || !SRAnim->GetbIsEquiping())
	{
		return;
	}
	if (!SRAnim->GetbIsAttacking())
	{
		FVector CameraLocation;
		FRotator CameraRotation;
		FVector FireLocation;
		FRotator FireRotation;

		if (!SRAnim->GetbZoomIn())
		{
			SRAnim->SetbIsAttacking(true);
			CameraLocation = GetActorLocation() + SpringArm->GetRelativeLocation() + Camera->GetRelativeLocation();
			CameraRotation = Camera->GetComponentRotation();

			FireLocation = CameraLocation + FTransform(CameraRotation).TransformVector(FVector(70.0f, 0.0f, 0.0f));
			FireRotation = CameraRotation;
		}
		else
		{
			SRAnim->SetbIsAttacking(true);
			CameraLocation = ADSCamera->GetComponentLocation();
			CameraRotation = ADSCamera->GetComponentRotation();

			FireLocation = CameraLocation + FTransform(CameraRotation).TransformVector(FVector(70.0f, 0.0f, 0.0f));
			FireRotation = CameraRotation;
		}
		FName ShellEjectSocket(TEXT("ShellEject"));
		FVector ShellEjectLocation = CurrentWeapon->GetMesh()->GetSocketLocation(ShellEjectSocket);
		FRotator ShellEjectRotation = CameraRotation;

		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
		
			FireRotation.Pitch += AimingAngle;
			
			// If the gauge control fails, the direction of the bullet will randomly bounce
			ApplyBulletAccuracy(SRPlayerController->GetGauge(), FireRotation);
			ASRBullet* Bullet = CurrentWeapon->ShootBullet(World, FireLocation, FireRotation, SpawnParams);
			if(Bullet)
			{
				float Roll = 0.0f;
				float Pitch = FMath::RandRange(-1.0f, 1.0f);
				float Yaw = FMath::RandRange(-1.0f, 1.0f);
				FRotator RandRotation = FRotator(Pitch, Yaw, Roll);
				SRPlayerController->SetControlRotation(GetControlRotation() + RandRotation);
			}

			ASREmptyBullet* EmptyBullet = CurrentWeapon->ShootEmptyBullet(World, ShellEjectLocation, ShellEjectRotation, SpawnParams);
		}

		SRAnim->PlayAttackMontage();
		
		// Add Particles to Muzzle and Add Sound
		FName MuzzleSocket(TEXT("Muzzle"));
		UGameplayStatics::SpawnEmitterAttached(CurrentWeapon->GetMuzzleParticle(), CurrentWeapon->GetMesh(), MuzzleSocket);
		UGameplayStatics::SpawnEmitterAttached(CurrentWeapon->GetBulletTrailParticle(), CurrentWeapon->GetMesh(), MuzzleSocket);

		UGameplayStatics::PlaySound2D(World, CurrentWeapon->GetAttackSound());

		SRPlayerController->ConsumeBullets(1);
		SRPlayerController->ChangebGauging(false);
	}
}

void ASRCharacter::Gauging()
{
	ASRPlayerController* PlayerController = Cast<ASRPlayerController>(GetController());
	if (PlayerController)
	{
		PlayerController->ChangeGauge(0.0f);
		PlayerController->ChangebGauging(true);
	}
}

// Adjust the direction of the bullet slightly according to the gauge of the bullet.
void ASRCharacter::ApplyBulletAccuracy(float Gauge, FRotator& FireRotation)
{
	float Pitch = 0.0f;
	float Yaw = 0.0f;
	const float MinUnder50 = 1.0f;
	const float MaxUnder50 = 1.5f;
	const float MinUnder80 = 0.3f;
	const float MaxUnder80 = 0.7f;
	if (Gauge == -1.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("CurrentGauge Error"));
	}

	if (Gauge < 50.0f)
	{
		Pitch = FMath::RandRange(MinUnder50, MaxUnder50);
		Yaw = FMath::RandRange(MinUnder50, MaxUnder50);
		
	}
	else if (Gauge < 80.0f)
	{
		Pitch = FMath::RandRange(MinUnder80, MaxUnder80);
		Yaw = FMath::RandRange(MinUnder80, MaxUnder80);
	}
	else if (Gauge < 120.0f)
	{

	}
	else if (Gauge < 150.0f)
	{
		Pitch = FMath::RandRange(MinUnder80, MaxUnder80);
		Yaw = FMath::RandRange(MinUnder80, MaxUnder80);
	}
	else
	{
		Pitch = FMath::RandRange(MinUnder50, MaxUnder50);
		Yaw = FMath::RandRange(MinUnder50, MaxUnder50);
	}
	int Num = FMath::RandRange(10, 99);
	(Num / 10) % 2 == 1 ? FireRotation.Pitch += Pitch : FireRotation.Pitch -= Pitch;
	(Num % 10) % 2 == 1 ? FireRotation.Yaw += Yaw : FireRotation.Yaw -= Yaw;
}

void ASRCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (SRAnim->GetbIsAttacking())
	{
		SRAnim->SetbIsAttacking(false);
	}
}