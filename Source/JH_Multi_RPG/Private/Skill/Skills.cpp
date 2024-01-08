// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Skills.h"
#include "GameFramework/Character.h"
#include "Animation/AnimMontage.h"

ASkills::ASkills()
{
	bReplicates = true;
}

void ASkills::SkillExecute(ACharacter* Character)
{
	
	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(SkillMontage);
}
