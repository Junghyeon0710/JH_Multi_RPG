// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/JHWidgetController.h"

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

