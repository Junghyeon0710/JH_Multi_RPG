// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/InventoryWidgetController.h"
#include "Inventory/JHInventoryComponent.h"
#include "Character/Component/HealthComponent.h"

void UInventoryWidgetController::BindCallbacksToFunctions()
{
	InventoryComponent->OnGoldChanged.AddLambda(
		[this](int32 NewGold)
		{
			//SetMoney(NewGold);
		}
	);
}

int32 UInventoryWidgetController::GetOwnerGold() const
{
	return InventoryComponent->GetGold();
}

float UInventoryWidgetController::GetOwnerHealth() const
{
	return HealthComponent->GetHealth();
}

float UInventoryWidgetController::GetOwnerMaxHealth() const
{
	return HealthComponent->GetMaxHealth();
}
