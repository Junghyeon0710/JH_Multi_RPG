// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillInput.h"
#include "Skills.generated.h"

/**
 * 
 */
UCLASS()
class JH_MULTI_RPG_API USkills : public UObject
{
	GENERATED_BODY()
private:
	friend class USkillComponent;
protected:
	UPROPERTY(EditDefaultsOnly)
	ESkillInput SkillInput;

	int32 SkllLevel = 0;
public:

private:
};
