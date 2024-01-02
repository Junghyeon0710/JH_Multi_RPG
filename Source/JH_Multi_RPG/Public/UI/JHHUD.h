// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "JHHUD.generated.h"


class UJHUserWidget;
class UJHWidgetController;
class UOverlayWidgetController;
/**
 * 
 */
UCLASS()
class JH_MULTI_RPG_API AJHHUD : public AHUD
{
	GENERATED_BODY()

public:
	void InitOverlay();
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

	UPROPERTY()
	TObjectPtr<UJHWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UJHWidgetController> OverlayWidgetControllerClass;

	 
};
