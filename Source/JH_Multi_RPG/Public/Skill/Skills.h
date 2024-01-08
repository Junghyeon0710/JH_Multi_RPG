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
	/** 스킬 실행*/
	void SkillExecute(ACharacter* Character);
protected:
	/** 스킬 이름*/
	UPROPERTY(EditDefaultsOnly)
	ESkillName SkillName;

	/** 스킬 Input*/
	UPROPERTY(EditDefaultsOnly)
	ESkillInput SkillInput;

	/** 스킬 실행 몽타추*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> SkillMontage;

};
