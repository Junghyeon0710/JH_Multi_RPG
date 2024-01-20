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

	InventoryComponent->OnUpdateItemInventoryUI.AddLambda(
		[this](const FInventoryItem& Item)
		{
			OnUpdateInventoryUISignature.Broadcast(Item);
		}
	);
}

const FInventoryItem& UInventoryWidgetController::GetOwnerInventoryItem() const
{
	return InventoryComponent->GetInventoryItem();
}

void UInventoryWidgetController::SetOwnerInventoryItem(const FSlotDataTable& Item, const int32& Index)
{
	InventoryComponent->GetInventoryItem().Swords[Index] = Item;
}

void UInventoryWidgetController::UsePotion(const FSlotDataTable& Item, const int& Index)
{
	if (LoadItemDataTable())
	{
		FItemDataTable* PotionItem = LoadItemDataTable()->FindRow<FItemDataTable>(Item.ItemId.RowName, TEXT(""));
		HealthComponent->IncreaseHealth(PotionItem->Power);
		InventoryComponent->PotionDecrease(Index);
	}
}

void UInventoryWidgetController::EquipWeapon(const FSlotDataTable& Item, const int& Index, bool& IsEquipped)
{
	if (LoadItemDataTable())
	{
		FItemDataTable* WeaponItem = LoadItemDataTable()->FindRow<FItemDataTable>(Item.ItemId.RowName, TEXT(""));

		if (Item.ItemType == EItemType::EIT_Sword)
		{
			IsEquipped = true;
			InventoryComponent->ServerEquipSword(WeaponItem->Mesh,Item,Index);
		
			return;
		}
		else
		{
			IsEquipped = true;
			InventoryComponent->ServerEquipShield(WeaponItem->Mesh,Item,Index);
			return;
		}
	}
	IsEquipped = false;
}

void UInventoryWidgetController::DropItem(const FSlotDataTable& Item, const int& Index)
{
	InventoryComponent->ServerDropInventoryItem(Item, Index);
}

UDataTable* UInventoryWidgetController::LoadItemDataTable()
{
	const FString DataTablePath = TEXT("/Script/Engine.DataTable'/Game/Blueprints/Inventory/Items/DataTable/DT_ItemDataTable.DT_ItemDataTable'");
	UDataTable* ItemDataTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *DataTablePath));
	return ItemDataTableObject;
}

const TArray<FSlotDataTable>& UInventoryWidgetController::GetOwnerEquipSword() const
{
	return InventoryComponent->GetEquipedSword();
}

const TArray<FSlotDataTable>& UInventoryWidgetController::GetOwnerEquipShield() const
{
	return InventoryComponent->GetEquipedShield();
}

void UInventoryWidgetController::OnDropEvent(const FSlotDataTable& SourceItem, const FSlotDataTable& TargetItem, const int32& SourceIndex, const int32& TargetIndex)
{
	InventoryComponent->ServerOnDropEvent(SourceItem, TargetItem, SourceIndex, TargetIndex);
}

const int32 UInventoryWidgetController::GetOwnerEquipSwordIndex() const
{
	return InventoryComponent->GetEquippedSwordIndex();
}

const int32 UInventoryWidgetController::GetOwnerEquipShiledIndex() const
{
	return InventoryComponent->GetEquippedShieldIndex();
}

