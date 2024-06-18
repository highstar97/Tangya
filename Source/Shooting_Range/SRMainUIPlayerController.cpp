#include "SRMainUIPlayerController.h"

#include "Blueprint/UserWidget.h"

ASRMainUIPlayerController::ASRMainUIPlayerController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_MAIN_C(TEXT("/Game/UI/UI_Main.UI_Main_C"));
	if (UI_MAIN_C.Succeeded())
	{
		MainWidgetClass = UI_MAIN_C.Class;
	}
}

void ASRMainUIPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!ensure(MainWidgetClass != nullptr)) return;

	MainWidget = CreateWidget<UUserWidget>(this, MainWidgetClass);
	if (!ensure(MainWidget != nullptr)) return;

	ToggleMainWidget(true);

	FInputModeUIOnly Mode;
	Mode.SetWidgetToFocus(MainWidget->GetCachedWidget());
	SetInputMode(Mode);
	bShowMouseCursor = true;
}

void ASRMainUIPlayerController::ToggleMainWidget(bool bIsNeedToTurnOn)
{
	if (!ensure(MainWidget != nullptr)) return;

	bIsNeedToTurnOn == true ? MainWidget->AddToViewport() : MainWidget->RemoveFromParent();
}