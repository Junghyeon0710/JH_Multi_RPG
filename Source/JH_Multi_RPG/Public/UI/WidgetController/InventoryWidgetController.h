// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/JHWidgetController.h"
#include "InventoryWidgetController.generated.h"

struct FInventoryItem;
struct FSlotDataTable;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGoldChangeSignature, int32, NewGold);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryItemAddSignature, const FInventoryItem&, Item);

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

	UFUNCTION(BlueprintPure)
	const FInventoryItem& GetOwnerInventoryItem() const;

	UFUNCTION(Server,Reliable,BlueprintCallable)
	void SeverUsePotion(const FSlotDataTable& Item, const int& Index);
};
