// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillComponent.h"
#include "Skill/Skills.h"
#include "Skill/SkillInfo.h"
#include "Net/UnrealNetwork.h"

USkillComponent::USkillComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USkillComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	DOREPLIFETIME_CONDITION(USkillComponent, ActivatableSkillNames,COND_OwnerOnly);
	DOREPLIFETIME(USkillComponent, ActivatableSkills);

}

const TArray<ESkillName>& USkillComponent::GetActivatableSkillNames() const
{
	return ActivatableSkillNames;
}

void USkillComponent::BeginPlay()
{
	Super::BeginPlay();
	
	/* 서버만 스킬을 가질 수 있습니다.**/
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		for (int32 i = 0; i < StartSkillsClass.Num(); i++)
		{
			ActivatableSkills.Add(GetWorld()->SpawnActor<ASkills>(StartSkillsClass[i]));
			ActivatableSkills[i]->SetOwner(GetOwner());
			ActivatableSkillNames.Add(ActivatableSkills[i]->SkillName);
		}
	}
}

void USkillComponent::ServerSkill_Implementation(ACharacter* Character, const ESkillInput& SkillInput)
{
	for (ASkills* Skill : ActivatableSkills)
	{
		if (Skill->SkillInput == SkillInput)
		{
			MultiSkill(Character, SkillInput, Skill);
		}
	}
}

void USkillComponent::MultiSkill_Implementation(ACharacter* Character, const ESkillInput& SkillInput, ASkills* Skill)
{
	if (Skill)
	{
		Skill->SkillExecute(Character);
	}

}

void USkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}
