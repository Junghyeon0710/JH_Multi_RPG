// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/JHWidgetController.h"
#include "InventoryWidgetController.generated.h"

struct FInventoryItem;
struct FSlotDataTable;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGoldChangeSignature, int32, NewGold);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryItemAddSignature, const FInventoryItem&, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateInventoryUISignature, const FInventoryItem&, Item);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class JH_MULTI_RPG_API UInventoryWidgetController : public UJHWidgetController
{
	GENERATED_BODY()
public:
	virtual void BindCallbacksToFunctions() override;
	
	UPROPERTY(BlueprintAssignable,Category="Gold")
	FOnGoldChangeSignature OnGoldChangeSignature;

	UPROPERTY(BlueprintAssignable, Category = "Item")
	FOnInventoryItemAddSignature OnInventoryItemAddSignature;

	UPROPERTY(BlueprintAssignable, Category = "Item")
	FOnUpdateInventoryUISignature OnUpdateInventoryUISignature;

	UFUNCTION(BlueprintPure)
	const FInventoryItem& GetOwnerInventoryItem() const;

	UFUNCTION(BlueprintCallable)
	void UsePotion(const FSlotDataTable& Item, const int& Index);

	UFUNCTION(BlueprintCallable)
	void EquipWeapon(const FSlotDataTable& Item, const int& Index,bool& IsEquipped);

	UFUNCTION(BlueprintCallable)
	void DropItem(const FSlotDataTable& Item, const int& Index);

	UDataTable* LoadItemDataTable();

	UFUNCTION(BlueprintPure)
	const TArray<FSlotDataTable>& GetOwnerEquipSword() const;

	UFUNCTION(BlueprintPure)
	const TArray<FSlotDataTable>& GetOwnerEquipShield() const;

public:
	UFUNCTION(BlueprintPure)
	const int32 GetOwnerEquipSwordIndex() const;
	UFUNCTION(BlueprintPure)
	const int32 GetOwnerEquipShiledIndex() const;

};
