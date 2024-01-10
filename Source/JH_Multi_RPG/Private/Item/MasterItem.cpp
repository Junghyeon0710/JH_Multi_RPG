// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/MasterItem.h"
#include "Components/SphereComponent.h"
#include "Interfaces/InventoryInterface.h"

AMasterItem::AMasterItem()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	ItemSphere = CreateDefaultSubobject<USphereComponent>(TEXT("ItemSphere"));
	SetRootComponent(ItemSphere);

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(RootComponent);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ItemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	ItemMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void AMasterItem::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		ItemSphere->OnComponentBeginOverlap.AddDynamic(this, &AMasterItem::OnOverlapBegin);
	}
}

void AMasterItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UInventoryInterface>())
	{
		/** ������ �� ���Ͱ� �������̽� ������ �ƾ��� �߰� �� ����*/
		IInventoryInterface::Execute_AddItem(OtherActor, this);
		Destroy();
	}
}

void AMasterItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

