// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Skill/SkillIInfoEnum.h"
#include "SkillComponent.generated.h"

class USkills;
class USkillInfo;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JH_MULTI_RPG_API USkillComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	friend class AJHCharacter;
public:	
	USkillComponent();

	UFUNCTION(BlueprintCallable)
	const TArray<ESkillName>& GetActivatableSkillNames() const;
protected:
	virtual void BeginPlay() override;

	UFUNCTION(Server,Reliable)
	void ServerSkill(ACharacter* Character,ESkillInput SkillInput);

	UFUNCTION(NetMulticast,Reliable)
	void MultiSkill(ACharacter* Character, ESkillInput SkillInput);

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	UPROPERTY()
	TArray<TObjectPtr<USkills>> ActivatableSkills;

	UPROPERTY()
	TArray<ESkillName> ActivatableSkillNames;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkillInfo> SkillInfo;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<USkills>> StartSkillsClass;
};
