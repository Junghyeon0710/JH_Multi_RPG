// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/JHInventoryComponent.h"
#include "UI/Widget/JHUserWidget.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Item/MasterItem.h"
#include "Item/DataTable/ItemDataTable.h"
#include "Kismet/KismetArrayLibrary.h"

UJHInventoryComponent::UJHInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UJHInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UJHInventoryComponent, Gold);
	DOREPLIFETIME(UJHInventoryComponent, InventoryItem);
}

void UJHInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	IenterWidget = CreateWidget<UJHUserWidget>(GetWorld(), IenterWidgetClass);

	//if (GetOwner() && GetOwner()->HasAuthority())
	//{
	//	InventoryItem.Swords.SetNum(SwordSize);
	//	InventoryItem.Shields.SetNum(ShieldSize);
	//	InventoryItem.Potion.SetNum(PotionSize);

	//}

}
void UJHInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsLocalPlayerController())
	{
		FHitResult HitResult;
		TraceItem(HitResult);
		if (HitResult.bBlockingHit)
		{
			IenterWidget->AddToViewport();
		}
		else
		{
			IenterWidget->RemoveFromParent();
		}
	}
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

void UJHInventoryComponent::TraceItem(FHitResult& HitResult)
{

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
}

AActor* UJHInventoryComponent::TraceItemToPickUp(FSlotDataTable& SlotDataTable, bool& FoundItem)
{
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		FHitResult HitResult;
		TraceItem(HitResult);
		AMasterItem* Item = Cast<AMasterItem>(HitResult.GetActor());
		if (Item)
		{
			SlotDataTable = Item->GetItemDataTable();
			FoundItem = true;
			return Item;
		}
	}
	FoundItem = false;
	return nullptr;
}

void UJHInventoryComponent::ServerAddToInventory_Implementation()
{
	FSlotDataTable PickupItemTable;
	bool bIsFoundItem;
	AActor* Item = TraceItemToPickUp(PickupItemTable, bIsFoundItem);

	if (bIsFoundItem && Item)
	{
		switch (PickupItemTable.ItemType)
		{
		case EItemType::EIT_Sword:
			if (AddItemToInventory(PickupItemTable, InventoryItem.Swords, SwordSize))
			{
				Item->Destroy();
			}
			break;
		case EItemType::EIT_Shield:
			if (AddItemToInventory(PickupItemTable, InventoryItem.Shields, ShieldSize))
			{
				Item->Destroy();
			}
			break;
		case EItemType::EIT_Potion:
			if (AddItemToInventory(PickupItemTable, InventoryItem.Potion, PotionSize))
			{
				Item->Destroy();
			}
			break;
		default:
			break;
		}
	
	}
}

void UJHInventoryComponent::OnRep_Gold(int32 OldGold)
{
	if (OnGoldChanged.IsBound())
	{
		OnGoldChanged.Broadcast(Gold);
	}

}

bool UJHInventoryComponent::AddItemToInventory(const FSlotDataTable& DataTable, TArray<FSlotDataTable>& InventoryItems, int32 Size)
{
	for (auto& Item : InventoryItems)
	{
		//먹은 아이템이랑 갖고있는 아이템이 같으면
		if (Item.ItemId.RowName == DataTable.ItemId.RowName)
		{
			FItemDataTable* ItemDataTable = DataTable.ItemId.DataTable->FindRow<FItemDataTable>(DataTable.ItemId.RowName, TEXT(""));
			//아이템 사이즈가 갖고있는 아이템과 인벤토리 아이템보다 크면 
			if (ItemDataTable->StacikSize >= Item.Quantiy + DataTable.Quantiy)
			{
				//아이템 갯수를 늘려줌
				Item.Quantiy = Item.Quantiy + DataTable.Quantiy;
				return true;
			}
		}
	}
	// 똑같은 아이템이 없고 인벤토리칸보다 적게 있으면 추가
	if (InventoryItems.Num() < Size)
	{
		InventoryItems.Add(DataTable);
		return true;
	}
	return false;
}

bool UJHInventoryComponent::IsLocalPlayerController()
{
	const ENetMode NetMode = GetNetMode();

	if (NetMode == NM_Standalone)
	{
		// Not networked.
		return true;
	}

	if (NetMode == NM_Client && GetOwner()->GetLocalRole() == ROLE_AutonomousProxy)
	{
		// Networked client in control.
		return true;
	}

	if (GetOwner()->GetRemoteRole() == ROLE_AutonomousProxy && GetOwner()->GetLocalRole() == ROLE_Authority)
	{
		// Local authority in control.
		return true;
	}

	return false;
}



