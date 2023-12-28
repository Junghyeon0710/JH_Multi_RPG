// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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

protected:
	virtual void BeginPlay() override;

	UFUNCTION(Server,Reliable)
	void ServerQSkill(ACharacter* Character);

	UFUNCTION(NetMulticast,Reliable)
	void MultiQSkill(ACharacter* Character);

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	TObjectPtr<USkills> Skill;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkillInfo> SkillInfo;
};
