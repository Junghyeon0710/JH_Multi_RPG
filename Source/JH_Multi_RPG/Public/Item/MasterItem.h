// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



	/**Properties */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties")
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties")
	FText ItemDescription;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Item Properties")
	TObjectPtr<UTexture2D> ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties")
	TObjectPtr<UStaticMesh> ItemStaticMesh;
	/* /Properties **/

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> ItemMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> ItemSphere;

};
 