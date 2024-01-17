// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/JHInventoryComponent.h"
#include "UI/Widget/JHUserWidget.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Item/MasterItem.h"
#include "Item/DataTable/ItemDataTable.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Interfaces/InventoryInterface.h"

UJHInventoryComponent::UJHInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UJHInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UJHInventoryComponent, Gold);
	DOREPLIFETIME_CONDITION(UJHInventoryComponent, InventoryItem,COND_OwnerOnly);
}

void UJHInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalPlayerController())
	{
		IenterWidget = CreateWidget<UJHUserWidget>(GetWorld(), IenterWidgetClass);
		JhInventoryWidget = CreateWidget<UJHUserWidget>(GetWorld(), JhUserWidgetClass);
	}
	
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		
		StartInventorySlot(InventoryItem.Swords, SwordSize);
		StartInventorySlot(InventoryItem.Shields, ShieldSize);
		StartInventorySlot(InventoryItem.Potion, PotionSize);

	}

}
void UJHInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsLocalPlayerController())
	{
		FSlotDataTable TraceItemDataTable;
		bool bFoundItem;
		TraceItemToPickUp(TraceItemDataTable, bFoundItem);
		if (IenterWidget && bFoundItem)
		{	
			if (OnTraceItemInfo.IsBound())
			{
				OnTraceItemInfo.Broadcast(TraceItemDataTable);
			}
			IenterWidget->AddToViewport();
	
		}
		else if(IenterWidget)
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

void UJHInventoryComponent::StartInventorySlot(TArray<FSlotDataTable>& Items, int32 Size)
{
	for (int i = 0; i < Size; i++)
	{
		Items.Add(FSlotDataTable());
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

	FHitResult HitResult;
	TraceItem(HitResult);
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
			if (AddItemToInventory(PickupItemTable, InventoryItem.Swords, SwordCount))
			{
				Item->Destroy();
			}
			break;
		case EItemType::EIT_Shield:
			if (AddItemToInventory(PickupItemTable, InventoryItem.Shields, ShieldCount))
			{
				Item->Destroy();
			}
			break;
		case EItemType::EIT_Potion:
			if (AddItemToInventory(PickupItemTable, InventoryItem.Potion, PotionCount))
			{
				Item->Destroy();
			}
			break;
		default:
			break;
		}
	}
}

void UJHInventoryComponent::ClientAddtoInventory_Implementation(const FInventoryItem& Item)
{
	OnInventoryItemAdd.Broadcast(Item);
}

void UJHInventoryComponent::OnRep_Gold(int32 OldGold)
{
	if (OnGoldChanged.IsBound())
	{
		OnGoldChanged.Broadcast(Gold);
	}
}

bool UJHInventoryComponent::AddItemToInventory(const FSlotDataTable& DataTable, TArray<FSlotDataTable>& InventoryItems, int32& Count)
{
	for (auto& Item : InventoryItems)
	{
		//���� �������̶� �����ִ� �������� ������
		if (Item.ItemId.RowName == DataTable.ItemId.RowName)
		{
			FItemDataTable* ItemDataTable = DataTable.ItemId.DataTable->FindRow<FItemDataTable>(DataTable.ItemId.RowName, TEXT(""));
			//������ ����� �����ִ� �����۰� �κ��丮 �����ۺ��� ũ�� 
			if (ItemDataTable->StacikSize >= Item.Quantiy + DataTable.Quantiy)
			{
				//������ ������ �÷���
				Item.Quantiy = Item.Quantiy + DataTable.Quantiy;
				ClientAddtoInventory(InventoryItem);
				return true;
			}
		}
	}
	// �Ȱ��� �������� ���� �κ��丮ĭ���� ���� ������ �߰�
	if (Count <= InventoryItems.Num() && InventoryItems[Count].Quantiy == 0)
	{		
		InventoryItems[Count].ItemId = DataTable.ItemId;
		InventoryItems[Count].ItemType = DataTable.ItemType;
		InventoryItems[Count].Quantiy = DataTable.Quantiy;		
		Count++;
		ClientAddtoInventory(InventoryItem);
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

void UJHInventoryComponent::PotionDecrease(const int32& Index)
{
	--InventoryItem.Potion[Index].Quantiy;
}

void UJHInventoryComponent::EquipSword(UStaticMesh* SwordMesh)
{
	if (GetOwner()->Implements<UInventoryInterface>())
	{
		IInventoryInterface::Execute_SetSword(GetOwner(),SwordMesh);
	}
}

void UJHInventoryComponent::EquipShield(UStaticMesh* ShieldMesh)
{
	if (GetOwner()->Implements<UInventoryInterface>())
	{
		IInventoryInterface::Execute_SetShield(GetOwner(), ShieldMesh);
	}
}



