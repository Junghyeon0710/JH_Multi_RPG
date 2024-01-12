// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/JHWidgetController.h"
#include "Inventory/JHInventoryComponent.h"
#include "Character/Component/HealthComponent.h"

void UJHWidgetController::SetWidgetControllerParms(const FWidgetControllerParms& Parms)
{
	SkillComponent = Parms.SkillComponent;
	InventoryComponent = Parms.InventoryComponent;
	HealthComponent = Parms.HealthComponent;
}

void UJHWidgetController::BindCallbacksToFunctions()
{
	/** �� ��Ʈ�ѷ����� �����ϼ���*/
}

int32 UJHWidgetController::GetOwnerGold() const
{
	return InventoryComponent->GetGold();
}

float UJHWidgetController::GetOwnerHealth() const
{
	return HealthComponent->GetHealth();
}

float UJHWidgetController::GetOwnerMaxHealth() const
{
	return HealthComponent->GetMaxHealth();
}