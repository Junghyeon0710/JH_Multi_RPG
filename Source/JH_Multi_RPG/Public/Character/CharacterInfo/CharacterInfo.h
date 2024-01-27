// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterInfo.generated.h"

USTRUCT(BlueprintType)
struct FCharacterInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,Category="CharacterInfo")
	FText Name;
};