// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/JHInventoryComponent.h"
#include "UI/Widget/JHUserWidget.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

UJHInventoryComponent::UJHInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UJHInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UJHInventoryComponent, Gold);
}

void UJHInventoryComponent::PressInventoryKey()
{
	bIsInventoryOpen = !bIsInventoryOpen;
	if (!bIsInventoryOpen)
	{
		if (JhInventoryWidget == nullptr)
		{
			JhInventoryWidget = CreateWidget<UJHUserWidget>(GetWorld(), JhUserWidgetClass);
		}
		JhInventoryWidget->AddToViewport();

	}
	else if (IsValid(JhInventoryWidget))
	{
		JhInventoryWidget->RemoveFromParent();
	}

}

void UJHInventoryComponent::AddToGold(int32 AddGold)
{
	Gold += AddGold;
	
	if (OnGoldChanged.IsBound())
	{
		OnGoldChanged.Broadcast(Gold);
	}
}

void UJHInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UJHInventoryComponent::OnRep_Gold(int32 OldGold)
{
	if (OnGoldChanged.IsBound())
	{
		OnGoldChanged.Broadcast(Gold);
	}

}

void UJHInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


