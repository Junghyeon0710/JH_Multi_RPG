// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/InventoryWidgetController.h"
#include "Inventory/JHInventoryComponent.h"

void UInventoryWidgetController::BindCallbacksToFunctions()
{
	InventoryComponent->OnGoldChanged.AddLambda(
		[this](int32 NewGold)
		{

		}
	);
	InventoryComponent->OnInventoryItemAdd.AddLambda(
		[this](const FInventoryItem& Item)
		{
		
			OnInventoryItemAddSignature.Broadcast(Item);
		}
	);
}

const FInventoryItem& UInventoryWidgetController::GetOwnerInventoryItem() const
{
	return InventoryComponent->GetInventoryItem();
}




