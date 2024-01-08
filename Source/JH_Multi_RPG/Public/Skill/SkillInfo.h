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

	/**��ų ���� / TMap�� ����Ͽ� �ð����⵵�� ����*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SkillInfo")
	TMap<ESkillName,FJHSkillInfo> SkillInformation;

	FJHSkillInfo FindSkillInfo(const ESkillName& SkillName, bool bLogNotFound = false) const;
};
