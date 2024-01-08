// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SkillIInfoEnum.h"
#include "SkillInfo.generated.h"

class UAnimMontage;

USTRUCT(BlueprintType)
struct FJHSkillInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ESkillInput SkillInput;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UTexture2D> SkillIcon = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText SkillContext = FText();

};

/**
 * 
 */
UCLASS()
class JH_MULTI_RPG_API USkillInfo : public UDataAsset
{
	GENERATED_BODY()
public:

	/**스킬 정보 / TMap을 사용하여 시간복잡도를 줄임*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SkillInfo")
	TMap<ESkillName,FJHSkillInfo> SkillInformation;

	FJHSkillInfo FindSkillInfo(const ESkillName& SkillName, bool bLogNotFound = false) const;
};
