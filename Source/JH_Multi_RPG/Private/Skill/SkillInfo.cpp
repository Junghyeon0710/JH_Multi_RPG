// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillInfo.h"

FJHSkillInfo USkillInfo::FindSkillInfo(const ESkillInput& SkillInput, bool bLogNotFound) const
{
	for (const FJHSkillInfo& info : SkillInformation)
	{
		if (info.SkillInput == SkillInput)
			return info;
	}
	return FJHSkillInfo();
}
