// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/InventoryWidgetController.h"
#include "Inventory/JHInventoryComponent.h"

void UInventoryWidgetController::BindCallbacksToFunctions()
{
	InventoryComponent->OnGoldChanged.AddLambda(
		[this](int32 NewGold)
		{
			OnGoldChangeSignature.Broadcast(NewGold);
		}
	);
}
