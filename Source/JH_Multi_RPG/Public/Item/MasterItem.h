// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enum/ItemTypes.h"
#include "DataTable/SlotDataTable.h"
#include "MasterItem.generated.h"


class USphereComponent;


UCLASS()
class JH_MULTI_RPG_API AMasterItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AMasterItem();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	FDataTableRowHandle MoneyDataHandle;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> ItemMesh;

protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> ItemSphere;

	/**Properties */
	UPROPERTY(EditAnywhere)
	FSlotDataTable ItemDataTable;

public:
	const FSlotDataTable& GetItemDataTable() const { return ItemDataTable; }
	void SetItemDataTable(const FSlotDataTable& Data) { ItemDataTable = Data; }
};
 