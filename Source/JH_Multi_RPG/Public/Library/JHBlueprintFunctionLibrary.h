// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JHBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class JH_MULTI_RPG_API UJHBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintPure,Category= "BluerpintLibrary|Inventory",meta = (DefaultToSelf= "WorldContextObject"))
	static class UInventoryWidgetController* GetInventoryWidgetController(const UObject* WorldContextObject);
	
};
