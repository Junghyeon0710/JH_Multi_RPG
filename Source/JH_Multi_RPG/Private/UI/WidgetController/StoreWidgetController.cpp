// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/StoreWidgetController.h"
#include "Inventory/JHInventoryComponent.h"

void UStoreWidgetController::BindCallbacksToFunctions()
{
	InventoryComponent->OnStoreGoldChanged.AddLambda(
		[this](int32 NewGold,bool bCanBuy)
		{
			OnGoldChangeSignature.Broadcast(NewGold, bCanBuy);
		}
	);
}

void UStoreWidgetController::BuyItem(const FSlotDataTable& Item)
{
   InventoryComponent->ServerBuyItem(Item);
}
