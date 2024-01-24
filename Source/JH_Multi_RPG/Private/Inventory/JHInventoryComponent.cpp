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
	DOREPLIFETIME(UJHInventoryComponent, InventoryItem);
	DOREPLIFETIME(UJHInventoryComponent, EquipedSword);
	DOREPLIFETIME(UJHInventoryComponent, EquipedShield);
	DOREPLIFETIME(UJHInventoryComponent, EquippedSwordIndex);
	DOREPLIFETIME(UJHInventoryComponent, EquippedShieldIndex);
}

void UJHInventoryComponent::ServerDropInventoryItem_Implementation(const FSlotDataTable& DataTable, const int32& Index)
{
	switch (DataTable.ItemType)
	{
	case EItemType::EIT_Sword:

		if (Index == EquippedSwordIndex && InventoryItem.Swords[Index].ItemId.RowName == DataTable.ItemId.RowName)
		{
			return;
		}
		SwordCount--;
		InventoryItem.Swords[Index] = FSlotDataTable(EItemType::EIT_Sword);
		OnUpdateItemInventoryUIBroadcast();

		break;
	case EItemType::EIT_Shield:

		if (Index == EquippedShieldIndex && InventoryItem.Shields[Index].ItemId.RowName == DataTable.ItemId.RowName)
		{
			return;
		}
		InventoryItem.Shields[Index] = FSlotDataTable(EItemType::EIT_Shield);
		OnUpdateItemInventoryUIBroadcast();

		break;
	case EItemType::EIT_Potion:
		InventoryItem.Potion[Index] = FSlotDataTable(EItemType::EIT_Potion);
		if (OnUpdateItemInventoryUI.IsBound())
		{
			OnUpdateItemInventoryUI.Broadcast(InventoryItem);
			PotionCount--;
		}
		break;
	default:
		break;
	}

	FActorSpawnParameters Parms;
	Parms.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	AMasterItem* Item = GetWorld()->SpawnActor<AMasterItem>(MasterItemClass, GetOwner()->GetTransform());
	Item->SetItemDataTable(DataTable);
	FItemDataTable* ItemDatatable = Item->GetItemDataTable().ItemId.DataTable->FindRow<FItemDataTable>(Item->GetItemDataTable().ItemId.RowName, TEXT(""));
	Item->ItemMesh->SetStaticMesh(ItemDatatable->Mesh);
}

void UJHInventoryComponent::ServerOnDropEvent_Implementation(const FSlotDataTable& SourceItem, const FSlotDataTable& TargetItem, const int32& SourceIndex, const int32& TargetIndex)
{
	switch (SourceItem.ItemType)
	{
	case EItemType::EIT_Sword:
		SwapDraggedItems(InventoryItem.Swords,
			SourceItem,
			TargetItem,
			SourceIndex,
			TargetIndex, EquippedSwordIndex);
		break;
	case EItemType::EIT_Shield:
		SwapDraggedItems(InventoryItem.Shields,
			SourceItem,
			TargetItem,
			SourceIndex,
			TargetIndex, EquippedShieldIndex);
		break;
	case EItemType::EIT_Potion:
		SwapDraggedItems(InventoryItem.Potion,
			SourceItem,
			TargetItem,
			SourceIndex,
			TargetIndex);
		break;
	default:
		break;
	}
	OnUpdateItemInventoryUIBroadcast();
}

void UJHInventoryComponent::ServerBuyItem_Implementation(const FSlotDataTable& Item)
{
	FItemDataTable* ItemDataTable = Item.ItemId.DataTable->FindRow<FItemDataTable>(Item.ItemId.RowName, TEXT(""));
	if (ItemDataTable)
	{
		float Price = ItemDataTable->BuyPrice * Item.Quantiy;
		if (Gold >= Price)
		{
			switch (Item.ItemType)
			{
			case EItemType::EIT_Sword:
				AddItemToInventory(Item, InventoryItem.Swords, SwordCount);
				break;
			case EItemType::EIT_Shield:
				AddItemToInventory(Item, InventoryItem.Shields, ShieldCount);
				break;
			case EItemType::EIT_Potion:
				AddItemToInventory(Item, InventoryItem.Potion, PotionCount);
				break;
			default:
				break;
			}
			Gold -= Price;
			if (OnGoldChanged.IsBound())
			{
				OnGoldChanged.Broadcast(Gold);
			}
		}
	}
}

void UJHInventoryComponent::SwapDraggedItems(TArray<FSlotDataTable>& MyItem, const FSlotDataTable& SourceItem, const FSlotDataTable& TargetItem, const int32& SourceIndex, const int32& TargetIndex, const int32& EquippedIndex)
{
	if (SourceIndex == EquippedIndex) return;
	else if (SourceItem.ItemId.RowName == TargetItem.ItemId.RowName)
	{
		return;
	}
	else if (SourceItem.ItemId.RowName != TargetItem.ItemId.RowName && TargetItem.Quantiy == 0)
	{
		MyItem[TargetIndex] = SourceItem;
		MyItem[SourceIndex] = TargetItem;
	}
	else if (SourceItem.ItemId.RowName != TargetItem.ItemId.RowName && TargetItem.Quantiy > 0)
	{
		MyItem[SourceIndex] = TargetItem;
		MyItem[TargetIndex] = SourceItem;
	}
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
		else if (IenterWidget)
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

void UJHInventoryComponent::OnRep_InventoryItem()
{
	OnUpdateItemInventoryUIBroadcast();
}

void UJHInventoryComponent::OnRep_EquipedSword()
{
	OnUpdateItemInventoryUIBroadcast();
}

void UJHInventoryComponent::OnRep_EquipedShield()
{
	OnUpdateItemInventoryUIBroadcast();
}

void UJHInventoryComponent::OnRep_EquippedSwordIndex()
{
	OnUpdateItemInventoryUIBroadcast();
}

void UJHInventoryComponent::OnRep_EquippedShieldIndex()
{
	OnUpdateItemInventoryUIBroadcast();
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
	if (Count <= InventoryItems.Num())
	{
		for (auto& Item : InventoryItems)
		{
			if (Item.Quantiy == 0)
			{
				Item = DataTable;
				Count++;
				ClientAddtoInventory(InventoryItem);
				return true;
			}
		}
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

void UJHInventoryComponent::ServerShieldDecrease_Implementation(const int32& Index)
{
	--InventoryItem.Shields[Index].Quantiy;
	OnUpdateItemInventoryUIBroadcast();
}

void UJHInventoryComponent::PotionDecrease_Implementation(const int32& Index)
{
	--InventoryItem.Potion[Index].Quantiy;
	OnUpdateItemInventoryUIBroadcast();
}

void UJHInventoryComponent::ServerSwordDecrease_Implementation(const int32& Index)
{
	--InventoryItem.Swords[Index].Quantiy;
	OnUpdateItemInventoryUIBroadcast();
}

void UJHInventoryComponent::ServerEquipSword_Implementation(UStaticMesh* SwordMesh, const FSlotDataTable& Item, const int32& Index)
{
	if (GetOwner()->Implements<UInventoryInterface>())
	{
		IInventoryInterface::Execute_SetSword(GetOwner(), SwordMesh);

		if (EquipedSword.Num() == 0)
		{
			EquipedSword.Add(Item);
			EquippedSwordIndex = Index;
			OnUpdateItemInventoryUIBroadcast();
			return;
		}
		EquipedSword[0] = Item;
		EquippedSwordIndex = Index;
		OnUpdateItemInventoryUIBroadcast();
	}
}

void UJHInventoryComponent::ServerEquipShield_Implementation(UStaticMesh* ShieldMesh, const FSlotDataTable& Item, const int32& Index)
{
	if (GetOwner()->Implements<UInventoryInterface>())
	{
		IInventoryInterface::Execute_SetShield(GetOwner(), ShieldMesh);

		if (EquipedShield.Num() == 0)
		{
			EquipedShield.Add(Item);
			EquippedShieldIndex = Index;
			OnUpdateItemInventoryUIBroadcast();
			return;
		}
		EquipedShield[0] = Item;
		EquippedShieldIndex = Index;
		OnUpdateItemInventoryUIBroadcast();
	}
}

void UJHInventoryComponent::OnUpdateItemInventoryUIBroadcast()
{
	if (OnUpdateItemInventoryUI.IsBound())
	{
		OnUpdateItemInventoryUI.Broadcast(InventoryItem);
	}
}
