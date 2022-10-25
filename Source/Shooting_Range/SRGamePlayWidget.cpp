// Fill out your copyright notice in the Description page of Project Settings.


#include "SRGamePlayWidget.h"
#include "Components/Button.h"
#include "SRPlayerController.h"
#include "Kismet/GameplayStatics.h"

void USRGamePlayWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ResumeButton = Cast<UButton>(GetWidgetFromName(TEXT("btnResume")));
	if (nullptr != ResumeButton)
	{
		ResumeButton->OnClicked.AddDynamic(this, &USRGamePlayWidget::OnResumeClicked);
	}

	ReturnToTitleButton = Cast<UButton>(GetWidgetFromName(TEXT("btnReturnToTitle")));
	if (nullptr != ReturnToTitleButton)
	{
		ReturnToTitleButton->OnClicked.AddDynamic(this, &USRGamePlayWidget::OnReturnToTitleClicked);
	}
}

void USRGamePlayWidget::OnResumeClicked()
{
	auto SRPlayerController = Cast<ASRPlayerController>(GetOwningPlayer());
	ensure(nullptr != SRPlayerController);

	RemoveFromParent();
	SRPlayerController->ChangeInputMode(true);
	SRPlayerController->SetPause(false);
}

void USRGamePlayWidget::OnReturnToTitleClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainLobby"));
}
