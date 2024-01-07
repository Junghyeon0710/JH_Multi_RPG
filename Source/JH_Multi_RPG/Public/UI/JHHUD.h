// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "JHHUD.generated.h"


class UJHUserWidget;
class UJHWidgetController;
class UOverlayWidgetController;
class USkillComponent;
/**
 * 
 */
UCLASS()
class JH_MULTI_RPG_API AJHHUD : public AHUD
{
	GENERATED_BODY()

public:
	//virtual void Tick(FGeometry MyGeometry, float InDeleaTIme) override;
	void InitOverlay(USkillComponent* SC);

private:

	UPROPERTY()
	TObjectPtr<UJHUserWidget> OverlayWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UJHUserWidget> OverlayWidgetClass;
	//
	//UPROPERTY()
	//TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	//UPROPERTY(EditAnywhere)
	//TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess = ture))
	TObjectPtr<UJHWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UJHWidgetController> OverlayWidgetControllerClass;
	 
};
