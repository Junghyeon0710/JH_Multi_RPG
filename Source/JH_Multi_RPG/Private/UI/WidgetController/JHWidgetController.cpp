// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/JHWidgetController.h"

void UJHWidgetController::SetWidgetControllerParms(const FWidgetControllerParms& Parms)
{
	SkillComponent = Parms.SkillComponent;
}

void UJHWidgetController::BindCallbacksToFunctions()
{
	/** 각 컨트롤러에서 구현하세요*/
}

