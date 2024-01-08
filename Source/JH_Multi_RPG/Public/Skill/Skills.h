// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkillIInfoEnum.h"
#include "Skills.generated.h"

class ACharacter;

/**
 * 
 */
UCLASS()
class JH_MULTI_RPG_API ASkills : public AActor
{
	GENERATED_BODY()
private:
	friend class USkillComponent;
public:
	ASkills();
	/** ��ų ����*/
	void SkillExecute(ACharacter* Character);
protected:
	/** ��ų �̸�*/
	UPROPERTY(EditDefaultsOnly)
	ESkillName SkillName;

	/** ��ų Input*/
	UPROPERTY(EditDefaultsOnly)
	ESkillInput SkillInput;

	/** ��ų ���� ��Ÿ��*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> SkillMontage;

};
