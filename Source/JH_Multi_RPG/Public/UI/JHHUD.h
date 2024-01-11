// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "JHHUD.generated.h"


class UJHUserWidget;
class UJHWidgetController;
class UOverlayWidgetController;
class USkillComponent;
class UJHInventoryComponent;
class UInventoryWidgetController;
struct FWidgetControllerParms;
class UHealthComponent;
/**
 * 
 */
UCLASS()
class JH_MULTI_RPG_API AJHHUD : public AHUD
{
	GENERATED_BODY()

public:
	//virtual void Tick(FGeometry MyGeometry, float InDeleaTIme) override;
	void InitOverlay(USkillComponent* SC, UJHInventoryComponent* IC, UHealthComponent* HC);

	UFUNCTION(BlueprintCallable)
	UInventoryWidgetController* GetInventoryWidgetController(const FWidgetControllerParms& Parms);

private:

	UPROPERTY()
	TObjectPtr<UJHUserWidget> OverlayWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UJHUserWidget> OverlayWidgetClass;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess = ture))
	TObjectPtr<UJHWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UJHWidgetController> OverlayWidgetControllerClass;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = ture))
	TObjectPtr<UInventoryWidgetController> InventoryWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UInventoryWidgetController> InventoryWidgetControllerClass;
	 
};
