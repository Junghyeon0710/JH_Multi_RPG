// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MoneyDataTable.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FMoneyDataTable : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	FName Name = FName();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Amount = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UStaticMesh> Mesh;
};

