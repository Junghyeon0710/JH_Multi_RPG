// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/JHHUD.h"
#include "UI/Widget/JHUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/WidgetController/JHWidgetController.h"

void AJHHUD::InitOverlay(USkillComponent* SC)
{
	OverlayWidget = CreateWidget<UJHUserWidget>(GetWorld(), OverlayWidgetClass);
	
	OverlayWidgetController = NewObject<UJHWidgetController>(this, OverlayWidgetControllerClass);
	const FWidgetControllerParms WidgetController(SC);
	OverlayWidgetController->SetWidgetControllerParms(WidgetController);
	
	OverlayWidget->SetWidgetController(OverlayWidgetController);
	OverlayWidgetController->BindCallbacksToFunctions();
	OverlayWidget->AddToViewport();

	
}