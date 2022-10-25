#include "SRPlayerController.h"
#include "SRGamePlayWidget.h"

ASRPlayerController::ASRPlayerController()
{
	static ConstructorHelpers::FClassFinder<USRGamePlayWidget> UI_PAUSE_C(TEXT("/Game/UI/UI_Pause.UI_Pause_C"));
	if (UI_PAUSE_C.Succeeded())
	{
		MenuWidgetClass = UI_PAUSE_C.Class;
	}
}

void ASRPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	UE_LOG(LogTemp, Log, TEXT("Player Controller PostInitializeComponetns"));
}

void ASRPlayerController::OnPossess(APawn* aPawn)
{
	UE_LOG(LogTemp, Log, TEXT("Player Controller OnPossess"));
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

void ASRPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ChangeInputMode(true);
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
