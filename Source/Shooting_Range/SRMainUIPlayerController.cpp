// Fill out your copyright notice in the Description page of Project Settings.


#include "SRMainUIPlayerController.h"
#include "Blueprint/UserWidget.h"

void ASRMainUIPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ensure(nullptr != UIWidgetClass);

	UIWidgetInstance = CreateWidget<UUserWidget>(this, UIWidgetClass);
	ensure(nullptr != UIWidgetInstance);

	UIWidgetInstance->AddToViewport();

	FInputModeUIOnly Mode;
	Mode.SetWidgetToFocus(UIWidgetInstance->GetCachedWidget());
	SetInputMode(Mode);
	bShowMouseCursor = true;
}
