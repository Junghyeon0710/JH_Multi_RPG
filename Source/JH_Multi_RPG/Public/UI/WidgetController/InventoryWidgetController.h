// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/JHWidgetController.h"
#include "InventoryWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGoldChangeSignature, int32, NewGold);

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
};
