// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterInfo.generated.h"

class AJHCharacter;
USTRUCT(BlueprintType)
struct FCharacterInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="CharacterInfo")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> Mesh;
};