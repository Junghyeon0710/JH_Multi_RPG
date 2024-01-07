// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillComponent.h"
#include "Skill/Skills.h"
#include "Skill/SkillInfo.h"

USkillComponent::USkillComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

const TArray<ESkillName>& USkillComponent::GetActivatableSkillNames() const
{
	return ActivatableSkillNames;
}

void USkillComponent::BeginPlay()
{
	Super::BeginPlay();
	
	for (int32 i = 0; i < StartSkillsClass.Num();i++ )
	{
		ActivatableSkills.Add(NewObject<USkills>(this, StartSkillsClass[i]));
		ActivatableSkillNames.Add(ActivatableSkills[i]->SkillName);
	}
}

void USkillComponent::ServerSkill_Implementation(ACharacter* Character, ESkillInput SkillInput)
{
	MultiSkill(Character,SkillInput);
}

void USkillComponent::MultiSkill_Implementation(ACharacter* Character, ESkillInput SkillInput)
{
	for(USkills* Skill : ActivatableSkills)
	{
		if (Skill->SkillInput == SkillInput)
		{
			Skill->SkillExecute(Character);
		}
	}
}

void USkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}
