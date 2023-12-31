// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/JHHUD.h"
#include "UI/Widget/JHUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

void AJHHUD::InitOverlay()
{
	OverlayWidget = CreateWidget<UJHUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
	OverlayWidget->SetWidgetController(OverlayWidgetController);
	OverlayWidget->AddToViewport();
}
