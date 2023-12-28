// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SkillInput.h"
#include "SkillInfo.generated.h"

class UAnimMontage;

USTRUCT(BlueprintType)
struct FJHSkillInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ESkillInput SkillInput;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> SkillMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UTexture2D> SkillIcon = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText SkillName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText SkillContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 SkillLevel;

};

/**
 * 
 */
UCLASS()
class JH_MULTI_RPG_API USkillInfo : public UDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SkillInfo")
	TArray<FJHSkillInfo> SkillInformation;

	FJHSkillInfo FindSkillInfo(const ESkillInput& SkillInput, bool bLogNotFound = false) const;
};
