// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Money.h"
#include <../Public/Item/DataTable/MoneyDataTable.h>
#include "Interfaces/InventoryInterface.h"

AMoney::AMoney()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AMoney::BeginPlay()
{
	Super::BeginPlay();
    
   
}

void AMoney::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	const FString DataTablePath = TEXT("/Script/Engine.DataTable'/Game/Blueprints/Items/Golds/DataTable/DT_MoneyDataTable.DT_MoneyDataTable'");
	UDataTable* MoneyDataTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *DataTablePath));
	
	if (MoneyDataTableObject)
	{
		MoneyDataHandle.DataTable = MoneyDataTableObject;
		FMoneyDataTable* MoneyDataTable = MoneyDataTableObject->FindRow<FMoneyDataTable>(MoneyDataHandle.RowName, TEXT(""));
		
		if (MoneyDataTable)
		{
			ItemMesh->SetStaticMesh(MoneyDataTable->Mesh);
		}
	}
}

void AMoney::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UInventoryInterface>())
	{
		/** 오버랩 된 액터가 인터페이스 있으면 아아템 추가 후 삭제*/
		IInventoryInterface::Execute_AddGold(OtherActor, this);
	}
}

void AMoney::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

