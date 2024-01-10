// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "JHWidgetController.generated.h"


class USkillInfo;
class USkillComponent;
class UJHInventoryComponent;


USTRUCT(BlueprintType)
struct FWidgetControllerParms
{
	GENERATED_BODY()

	FWidgetControllerParms() {}
	FWidgetControllerParms(USkillComponent* SC, UJHInventoryComponent* IC) :
		SkillComponent(SC), InventoryComponent(IC){}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USkillComponent> SkillComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UJHInventoryComponent> InventoryComponent;


};
/**
 * 
 */
UCLASS()
class JH_MULTI_RPG_API UJHWidgetController : public UObject
{
	GENERATED_BODY()
public:

	void SetWidgetControllerParms(const FWidgetControllerParms& Parms);
	virtual void BindCallbacksToFunctions();
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SkillInfo")
	TObjectPtr<USkillInfo> SkillInfo;

	UPROPERTY(BlueprintReadOnly, Category = "SkillComponent")
	TObjectPtr<USkillComponent> SkillComponent;

	UPROPERTY(BlueprintReadOnly, Category= "InventoryComponent")
	TObjectPtr<UJHInventoryComponent> InventoryComponent;
};
