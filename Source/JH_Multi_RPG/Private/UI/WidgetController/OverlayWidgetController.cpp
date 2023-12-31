// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"
#include "Skill/SkillComponent.h"
#include "Skill/SkillInfo.h"

void UOverlayWidgetController::BindCallbacksToFunctions()
{
	for (auto& SkillName : SkillComponent->GetActivatableSkillNames())
	{
		FJHSkillInfo Info = SkillInfo->FindSkillInfo(SkillName);
		SkillInfoSignature.Broadcast(Info);
	}
}

