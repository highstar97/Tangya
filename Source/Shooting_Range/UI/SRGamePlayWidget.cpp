#include "SRGamePlayWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

#include "SRPlayerController.h"

void USRGamePlayWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!ensure(Button_Resume != nullptr)) return;
	Button_Resume->OnClicked.AddDynamic(this, &USRGamePlayWidget::OnResumeClicked);

	if (!ensure(Button_ReturnToTitle != nullptr)) return;
	Button_ReturnToTitle->OnClicked.AddDynamic(this, &USRGamePlayWidget::OnReturnToTitleClicked);

	if (!ensure(Button_Setting != nullptr)) return;
	Button_Setting->OnClicked.AddDynamic(this, &USRGamePlayWidget::OnSettingClicked);
}

void USRGamePlayWidget::OnResumeClicked()
{
	ASRPlayerController* SRPlayerController = Cast<ASRPlayerController>(GetOwningPlayer());
	if (!ensure(SRPlayerController != nullptr)) return;

	SRPlayerController->TogglePauseWidget(false);
	SRPlayerController->ChangeInputMode(EInputMode::GAMEONLY);
	SRPlayerController->SetPause(false);
}

void USRGamePlayWidget::OnReturnToTitleClicked()
{
	ASRPlayerController* SRPlayerController = Cast<ASRPlayerController>(GetOwningPlayer());
	if (!ensure(SRPlayerController != nullptr)) return;

	SRPlayerController->TogglePauseWidget(false);
	SRPlayerController->ChangeInputMode(EInputMode::UIONLY);
	SRPlayerController->SetPause(false);

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainLobby"));
}

void USRGamePlayWidget::OnSettingClicked()
{
	ASRPlayerController* SRPlayerController = Cast<ASRPlayerController>(GetOwningPlayer());
	if (!ensure(SRPlayerController != nullptr)) return;

	SRPlayerController->TogglePauseWidget(false);
	SRPlayerController->ToggleSettingWidget(true);
}