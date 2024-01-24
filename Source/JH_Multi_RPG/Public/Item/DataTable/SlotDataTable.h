// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "../../../../JH_Multi_RPG/Public/Item/Enum/ItemTypes.h"
#include "SlotDataTable.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FSlotDataTable : public FTableRowBase
{
	FSlotDataTable() {}
	FSlotDataTable(EItemType Type) :
	ItemType(Type) {}

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDataTableRowHandle ItemId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quantiy = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType ItemType;
};

