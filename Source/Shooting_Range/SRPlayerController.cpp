#include "SRPlayerController.h"
#include "Blueprint/UserWidget.h"

ASRPlayerController::ASRPlayerController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUDDY_C(TEXT("/Game/Blueprints/Huddy_BP.Huddy_BP_C"));
	if (UI_HUDDY_C.Succeeded())
	{
		HuddyWidgetClass = UI_HUDDY_C.Class;
	}
}

void ASRPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);

	HuddyWidget = CreateWidget<UUserWidget>(this, HuddyWidgetClass);
	HuddyWidget->AddToViewport();
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