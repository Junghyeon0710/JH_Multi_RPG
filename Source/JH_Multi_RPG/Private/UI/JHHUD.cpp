// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/JHHUD.h"
#include "UI/Widget/JHUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/WidgetController/JHWidgetController.h"
#include "UI/WidgetController/InventoryWidgetController.h"

void AJHHUD::InitOverlay(USkillComponent* SC, UJHInventoryComponent* IC)
{
	OverlayWidget = CreateWidget<UJHUserWidget>(GetWorld(), OverlayWidgetClass);
	
	OverlayWidgetController = NewObject<UJHWidgetController>(this, OverlayWidgetControllerClass);
	const FWidgetControllerParms WidgetController(SC,IC);
	OverlayWidgetController->SetWidgetControllerParms(WidgetController);
	

	OverlayWidget->SetWidgetController(OverlayWidgetController);
	OverlayWidgetController->BindCallbacksToFunctions();
	OverlayWidget->AddToViewport();

}

UInventoryWidgetController* AJHHUD::GetInventoryWidgetController(const FWidgetControllerParms& Parms)
{
	if (InventoryWidgetController == nullptr)
	{
		InventoryWidgetController = NewObject<UInventoryWidgetController>(this, InventoryWidgetControllerClass);
		InventoryWidgetController->SetWidgetControllerParms(Parms);
		InventoryWidgetController->BindCallbacksToFunctions();
	}
	return InventoryWidgetController;
}
