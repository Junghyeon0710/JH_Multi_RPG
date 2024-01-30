// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "../Character/CharacterInfo/CharacterInfo.h"
#include "JHGameMode.generated.h"

/**
 * 
 */
class AJHCharacter;

UCLASS()
class JH_MULTI_RPG_API AJHGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	void CharacterJoin(AJHCharacter* Player, const FCharacterInfo& PlayerInfo);
	void UpdateAllCharacter();

	UPROPERTY()
	TArray<TObjectPtr<AJHCharacter>> PlayerCharacters;

	UPROPERTY()
	TArray<FCharacterInfo> PlayerCharacterInfos;
};
