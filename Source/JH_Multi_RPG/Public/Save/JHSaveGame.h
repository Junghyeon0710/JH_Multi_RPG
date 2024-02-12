// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "../Character/CharacterInfo/CharacterInfo.h"
#include "JHSaveGame.generated.h"

/**
 * 
 */
class USkeletalMeshComponent;

UCLASS()
class JH_MULTI_RPG_API UJHSaveGame : public USaveGame
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FCharacterInfo CharacterInfo;
};