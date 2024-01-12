// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/JHInventoryComponent.h"
#include "UI/Widget/JHUserWidget.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Item/MasterItem.h"

UJHInventoryComponent::UJHInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
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

AActor* UJHInventoryComponent::TraceItemToPickUp(FSlotDataTable& SlotDataTable, bool& FoundItem)
{
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	FCollisionResponseParams parms;
		
	FVector Start = GetOwner()->GetActorLocation() - FVector(0.f, 0.f, 60.f);
	FVector End = Start + GetOwner()->GetActorForwardVector() * 300.f;
	GetWorld()->SweepSingleByChannel(
		HitResult,
		Start,
		End,
		FQuat::Identity,
		ECollisionChannel::ECC_Visibility,
		FCollisionShape::MakeSphere(30),
		CollisionParams
	);
	
	AMasterItem* Item = Cast<AMasterItem>(HitResult.GetActor());
	if (Item)
	{
		SlotDataTable = Item->GetItemDataTable();
		FoundItem = true;
		return Item;
	}

	FoundItem = false;
	return nullptr;
}

void UJHInventoryComponent::BeginPlay()
{
	Super::BeginPlay();


	IenterWidget = CreateWidget<UJHUserWidget>(GetWorld(), IenterWidgetClass);


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

	FSlotDataTable SlotDataTable;
	bool Founditem;
	TraceItemToPickUp(SlotDataTable,Founditem);
	if (Founditem)
	{
		IenterWidget->AddToViewport();
	}
	else
	{
		IenterWidget->RemoveFromParent();
	}
}


