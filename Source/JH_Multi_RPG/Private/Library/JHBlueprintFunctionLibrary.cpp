// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/JHBlueprintFunctionLibrary.h"
#include "UI/JHHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Character/JHCharacter.h"
#include "UI/WidgetController/JHWidgetController.h"


UInventoryWidgetController* UJHBlueprintFunctionLibrary::GetInventoryWidgetController(const UObject* WorldContextObject)
{    
    if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
    {
        if (AJHHUD* HUD = Cast<AJHHUD>(PlayerController->GetHUD()))
        {
            if (ACharacter* Character = UGameplayStatics::GetPlayerCharacter(WorldContextObject, 0))
            {         
                AJHCharacter* JHCharacter = Cast<AJHCharacter>(Character);
                FWidgetControllerParms Parms;
                Parms.SkillComponent = JHCharacter->GetSKillComponent();
                Parms.InventoryComponent = JHCharacter->GetInventoryComponent();
                Parms.HealthComponent = JHCharacter->GetHealthComponent();
              
                return  HUD->GetInventoryWidgetController(Parms);
            }
        }  
    }
    return nullptr;
}

UStoreWidgetController* UJHBlueprintFunctionLibrary::GetStoreWidgetController(const UObject* WorldContextObject)
{
    if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
    {
        if (AJHHUD* HUD = Cast<AJHHUD>(PlayerController->GetHUD()))
        {
            if (ACharacter* Character = UGameplayStatics::GetPlayerCharacter(WorldContextObject, 0))
            {
                AJHCharacter* JHCharacter = Cast<AJHCharacter>(Character);
                FWidgetControllerParms Parms;
                Parms.SkillComponent = JHCharacter->GetSKillComponent();
                Parms.InventoryComponent = JHCharacter->GetInventoryComponent();
                Parms.HealthComponent = JHCharacter->GetHealthComponent();

                return  HUD->GetStoreWidgetController(Parms);
            }
        }
    }
    return nullptr;
}
