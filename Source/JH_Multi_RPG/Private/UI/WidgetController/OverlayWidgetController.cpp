// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"
#include "Skill/SkillComponent.h"
#include "Skill/SkillInfo.h"

void UOverlayWidgetController::BindCallbacksToFunctions()
{
	for (auto& Info : SkillComponent->GetActivatableSkillNames())
	{
		FJHSkillInfo Skill = SkillInfo->FindSkillInfo(Info);
		SkillInfoSignature.Broadcast(Skill);
	}
}

