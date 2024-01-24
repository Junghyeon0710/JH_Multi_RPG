// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JHInventoryComponent.generated.h"

class UJHUserWidget;
class AMasterItem;
class AJHCharacter;
struct FSlotDataTable;

USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TArray<FSlotDataTable> Swords;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FSlotDataTable> Shields;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FSlotDataTable> Potion;

};

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGoldChanged, int32 /* Gold*/,bool bCanBuy /*CanBuy? */);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInventoryItemAdd, const FInventoryItem& Item);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTraceItemInfo, const FSlotDataTable& Item);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdateItemInventoryUI, const FInventoryItem& Item);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JH_MULTI_RPG_API UJHInventoryComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	friend AJHCharacter;
public:	
	UJHInventoryComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const override;

	void PressInventoryKey();
	void AddToGold(int32 AddGold);
	void StartInventorySlot(TArray<FSlotDataTable>& Items,int32 Size);

	void TraceItem(FHitResult& HitResult);
	AActor* TraceItemToPickUp(FSlotDataTable& SlotDataTable,bool& FoundItem);
	
	UFUNCTION(Server, Reliable)
	void ServerAddToInventory();

	UFUNCTION(Client, Reliable)
	void ClientAddtoInventory(const FInventoryItem& Item);

	bool AddItemToInventory(const FSlotDataTable& DataTable, TArray<FSlotDataTable>& InventoryItems, int32& count);

	bool IsLocalPlayerController();

	UFUNCTION(Server, Reliable)
	void PotionDecrease(const int32& Index);
	UFUNCTION(Server, Reliable)
	void ServerSwordDecrease(const int32& Index);
	UFUNCTION(Server, Reliable)
	void ServerShieldDecrease(const int32& Index);

	UFUNCTION(Server, Reliable)
	void ServerEquipSword(UStaticMesh* SwordMesh,const FSlotDataTable& Item, const int32& Index);
	UFUNCTION(Server, Reliable)
	void ServerEquipShield(UStaticMesh* ShieldMesh, const FSlotDataTable& Item, const int32& Index);

	UFUNCTION(Server, Reliable)
	void ServerDropInventoryItem(const FSlotDataTable& DataTable, const int32& Index);

	UFUNCTION(Server, Reliable)
	void ServerOnDropEvent(const FSlotDataTable& SourceItem, const FSlotDataTable& TargetItem, const int32& SourceIndex, const int32& TargetIndex);

	UFUNCTION(Server, Reliable)
	void ServerBuyItem(const FSlotDataTable& Item);
	
	void SwapDraggedItems(TArray<FSlotDataTable>& MyItem, const FSlotDataTable& SourceItem, const FSlotDataTable& TargetItem, const int32& SourceIndex, const int32& TargetIndex, const int32& EquippedIndex = -1);
	FOnGoldChanged OnStoreGoldChanged;
	FOnInventoryItemAdd OnInventoryItemAdd;
	FOnTraceItemInfo OnTraceItemInfo;
	FOnUpdateItemInventoryUI OnUpdateItemInventoryUI;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UJHUserWidget> JhUserWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UJHUserWidget> JhInventoryWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UJHUserWidget> IenterWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UJHUserWidget> IenterWidget;

	UPROPERTY(EditAnywhere,ReplicatedUsing = OnRep_Gold)
	int32 Gold;

	UFUNCTION()
	void OnRep_Gold(int32 OldGold);

	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_InventoryItem, BlueprintReadOnly)
	FInventoryItem InventoryItem;
	
	UFUNCTION()
	void OnRep_InventoryItem();

	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_EquipedSword, Category = "Equip")
	TArray<FSlotDataTable> EquipedSword;

	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_EquipedSword, Category = "Equip")
	TArray<FSlotDataTable> EquipedShield;

	UFUNCTION()
	void OnRep_EquipedSword();

	UFUNCTION()
	void OnRep_EquipedShield();

	UPROPERTY(ReplicatedUsing = OnRep_EquippedSwordIndex, VisibleAnywhere, Category = "Count")
	int32 EquippedSwordIndex = -1;

	UPROPERTY(ReplicatedUsing =OnRep_EquippedShieldIndex, VisibleAnywhere, Category = "Count")
	int32 EquippedShieldIndex = -1;

	UFUNCTION()
	void OnRep_EquippedSwordIndex();

	UFUNCTION()
	void OnRep_EquippedShieldIndex();

	UPROPERTY(EditAnywhere, Replicated)
	bool bCanBuy;

private:

	bool bIsInventoryOpen = true;
	
	UPROPERTY(EditAnywhere,Category="Size")
	int32 SwordSize = 10;

	UPROPERTY(EditAnywhere, Category = "Size")	
	int32 ShieldSize = 10;

	UPROPERTY(EditAnywhere, Category = "Size")
	int32 PotionSize = 10;

	UPROPERTY(EditAnywhere, Category = "Count")
	int32 SwordCount = 0;

	UPROPERTY(EditAnywhere, Category = "Count")
	int32 ShieldCount = 0;

	UPROPERTY(EditAnywhere, Category = "Count")
	int32 PotionCount = 0;


	UPROPERTY(EditAnywhere, Category = "Spawn Actor")
	TSubclassOf<AMasterItem> MasterItemClass;

public:

	FORCEINLINE int32 GetGold() const { return Gold; }
	FORCEINLINE FInventoryItem& GetInventoryItem() { return InventoryItem; }
	FORCEINLINE const TArray<FSlotDataTable>& GetEquipedSword() const { return EquipedSword; }
	FORCEINLINE const TArray<FSlotDataTable>& GetEquipedShield() const { return EquipedShield; }
	FORCEINLINE int32 GetEquippedSwordIndex() const { return EquippedSwordIndex; }
	FORCEINLINE int32 GetEquippedShieldIndex() const { return EquippedShieldIndex; }
	FORCEINLINE void SetEquippedSwordIndex(int32 Index) { EquippedSwordIndex = Index; }
	FORCEINLINE void SetEquippedShieldIndex(int32 Index) { EquippedShieldIndex = Index; }
	void OnUpdateItemInventoryUIBroadcast();
};
