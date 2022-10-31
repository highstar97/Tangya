#include "SRPlayerController.h"
#include "SRPlayerState.h"
#include "SRGamePlayWidget.h"
#include "Blueprint/UserWidget.h"

ASRPlayerController::ASRPlayerController()
{
	static ConstructorHelpers::FClassFinder<USRGamePlayWidget> UI_PAUSE_C(TEXT("/Game/UI/UI_Pause.UI_Pause_C"));
	if (UI_PAUSE_C.Succeeded())
	{
		MenuWidgetClass = UI_PAUSE_C.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUDDY_C(TEXT("/Game/Blueprints/Huddy_BP.Huddy_BP_C"));
	if (UI_HUDDY_C.Succeeded())
	{
		HuddyWidgetClass = UI_HUDDY_C.Class;
	}
}

void ASRPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	UE_LOG(LogTemp, Warning, TEXT("Player Controller PostInitializeComponents"));
}

void ASRPlayerController::OnPossess(APawn* aPawn)
{
	UE_LOG(LogTemp, Warning, TEXT("Player Controller OnPossess"));
	Super::OnPossess(aPawn);
}

void ASRPlayerController::ChangeInputMode(bool bGameMode)
{
	if (bGameMode)
	{
		SetInputMode(GameInputMode);
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(UIInputMode);
		bShowMouseCursor = true;
	}
}

void ASRPlayerController::AddGameScore(int EarnedScore)
{
	SRPlayerState->AddGameScore(EarnedScore);
}

void ASRPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputMode;
	ChangeInputMode(true);

	PlayerCameraManager->ViewPitchMin = -45.0f;
	PlayerCameraManager->ViewPitchMax = 45.0f;

	HuddyWidget = CreateWidget<UUserWidget>(this, HuddyWidgetClass);
	HuddyWidget->AddToViewport();

	SRPlayerState = Cast<ASRPlayerState>(PlayerState);
}

void ASRPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("GamePause"), EInputEvent::IE_Pressed, this, &ASRPlayerController::OnGamePause);
}

void ASRPlayerController::OnGamePause()
{
	MenuWidget = CreateWidget<USRGamePlayWidget>(this, MenuWidgetClass);
	ensure(nullptr != MenuWidget);
	MenuWidget->AddToViewport(3);

	SetPause(true);
	ChangeInputMode(false);
}
