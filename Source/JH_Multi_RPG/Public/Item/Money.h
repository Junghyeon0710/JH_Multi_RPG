// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MasterItem.h"

#include "Money.generated.h"



UCLASS()
class JH_MULTI_RPG_API AMoney : public AMasterItem
{
	GENERATED_BODY()
	
public:	
	AMoney();
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName Name = FName();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Amount = 0;




};
