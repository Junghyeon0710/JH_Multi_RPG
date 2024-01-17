// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/InventoryWidgetController.h"
#include "Inventory/JHInventoryComponent.h"
#include "Character/Component/HealthComponent.h"
#include "Item/MasterItem.h"
#include "Item/DataTable/ItemDataTable.h"

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

void UInventoryWidgetController::SeverUsePotion_Implementation(const FSlotDataTable& Item, const int& Index)
{
	const FString DataTablePath = TEXT("/Script/Engine.DataTable'/Game/Blueprints/Inventory/Items/DataTable/DT_ItemDataTable.DT_ItemDataTable'");
	UDataTable* ItemDataTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *DataTablePath));
	if (ItemDataTableObject)
	{
		FItemDataTable* PotionItem = ItemDataTableObject->FindRow<FItemDataTable>(Item.ItemId.RowName, TEXT(""));
		HealthComponent->IncreaseHealth(PotionItem->Power);
		InventoryComponent->PotionDecrease(Index);
	}
	// Item.ItemId.RowName
}




