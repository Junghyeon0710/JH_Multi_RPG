// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "../../../../JH_Multi_RPG/Public/Item/Enum/ItemTypes.h"
#include "SlotDataTable.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FDSDSlotDataTable : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FDataTableRowHandle ItemId;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Quantiy = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EItemType ItemType;
};

UCLASS()
class JH_MULTI_RPG_API ASlotDataTablea : public AActor
{
	GENERATED_BODY()


};