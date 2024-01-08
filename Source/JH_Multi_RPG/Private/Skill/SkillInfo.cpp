// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillInfo.h"

FJHSkillInfo USkillInfo::FindSkillInfo(const ESkillName& SkillName, bool bLogNotFound) const
{
	const FJHSkillInfo* Info = SkillInformation.Find(SkillName);
	if (Info)
	{
		return *Info;
	}
	
	if (bLogNotFound)
	{
		UE_LOG(LogTemp,Error,TEXT("Not SkillInfo"))
	}

	return FJHSkillInfo();
}
