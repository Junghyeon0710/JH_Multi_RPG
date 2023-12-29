// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillIInfoEnum.h"
#include "Skills.generated.h"

class ACharacter;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class JH_MULTI_RPG_API USkills : public UObject
{
	GENERATED_BODY()
private:
	friend class USkillComponent;
public:
	void SkillExecute(ACharacter* Character);

	UPROPERTY(EditDefaultsOnly)
	ESkillInput SkillInput;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> SkillMontage;

private:

};
