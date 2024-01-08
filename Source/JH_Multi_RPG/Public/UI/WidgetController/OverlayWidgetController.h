// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/JHWidgetController.h"
#include "OverlayWidgetController.generated.h"

struct FJHSkillInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSkillInfoSignature, const FJHSkillInfo&, SkillInfo);



/**
 * 
 */
UCLASS(BlueprintType,Blueprintable)
class JH_MULTI_RPG_API UOverlayWidgetController : public UJHWidgetController
{
	GENERATED_BODY()
public:
	virtual void BindCallbacksToFunctions() override;

	UPROPERTY(BlueprintAssignable,Category="SKillInfo")
	FSkillInfoSignature SkillInfoSignature;

};


