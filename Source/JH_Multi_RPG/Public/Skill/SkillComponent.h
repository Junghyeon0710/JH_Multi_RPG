// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Skill/SkillIInfoEnum.h"
#include "SkillComponent.generated.h"

class ASkills;
class USkillInfo;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JH_MULTI_RPG_API USkillComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	friend class AJHCharacter;
public:	
	USkillComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const;

	UFUNCTION(BlueprintCallable)
	const TArray<ESkillName>& GetActivatableSkillNames() const;
protected:
	virtual void BeginPlay() override;

	UFUNCTION(Server,Reliable)
	void ServerSkill(ACharacter* Character,const ESkillInput& SkillInput);

	UFUNCTION(NetMulticast,Reliable)
	void MultiSkill(ACharacter* Character, ASkills* Skill);


private:
	UPROPERTY()
	TArray<TObjectPtr<ASkills>> ActivatableSkills;

	UPROPERTY(Replicated)
	TArray<ESkillName> ActivatableSkillNames;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkillInfo> SkillInfo;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<ASkills>> StartSkillsClass;
};
