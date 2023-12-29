// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillInfo.h"

FJHSkillInfo USkillInfo::FindSkillInfo(const ESkillName& SkillName, bool bLogNotFound) const
{
	for (const FJHSkillInfo& info : SkillInformation)
	{
		if (info.SkillName == SkillName)
			return info;
	}
	return FJHSkillInfo();
}
