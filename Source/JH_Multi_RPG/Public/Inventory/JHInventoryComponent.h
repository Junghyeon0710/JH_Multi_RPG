// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JHInventoryComponent.generated.h"

class UJHUserWidget;
class AMasterItem;
class AJHCharacter;
struct FSlotDataTable;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGoldChanged, int32 /* Gold*/);

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

	AActor* TraceItemToPickUp(FSlotDataTable& SlotDataTable,bool& FoundItem);

	FOnGoldChanged OnGoldChanged;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UJHUserWidget> JhUserWidgetClass;

	UPROPERTY()
	TObjectPtr<UJHUserWidget> JhInventoryWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UJHUserWidget> IenterWidgetClass;

	UPROPERTY()
	TObjectPtr<UJHUserWidget> IenterWidget;

	UPROPERTY(VisibleAnywhere,ReplicatedUsing = OnRep_Gold)
	int32 Gold;

	UFUNCTION()
	void OnRep_Gold(int32 OldGold);

private:

	bool bIsInventoryOpen = true;
public:

	FORCEINLINE int32 GetGold() const { return Gold; }
};
