// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillComponent.h"
#include "GameFramework/Character.h"
#include "Animation/AnimMontage.h"
#include "Skill/Skills.h"
#include "Skill/SkillInfo.h"
#include "Skill/SkillInput.h"


USkillComponent::USkillComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USkillComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void USkillComponent::ServerQSkill_Implementation(ACharacter* Character)
{
	MultiQSkill(Character);
}

void USkillComponent::MultiQSkill_Implementation(ACharacter* Character)
{
	FJHSkillInfo JHSkillInfo = SkillInfo->FindSkillInfo(ESkillInput::ESI_InputQ);
	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(JHSkillInfo.SkillMontage);

}

void USkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}
