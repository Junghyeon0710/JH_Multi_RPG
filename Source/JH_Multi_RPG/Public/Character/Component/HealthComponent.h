// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class AJhCharacter;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnHeatlhChanged, float /* Health*/);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JH_MULTI_RPG_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	friend AJhCharacter;
public:	

	UHealthComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const override;

	void IncreaseHealth(float AddHealth);
	void DecreaseHealth(float MinusHealth);

	FOnHeatlhChanged OnHeatlhChanged;
protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_Health, Category = "Health")
	float Health = 100.f;

	UPROPERTY(EditAnywhere, Category = "Health")
	float MaxHealth = 100.f;

	UFUNCTION()
	void OnRep_Health(float OldHealth);

public:

	FORCEINLINE float GetHealth() const { return Health; }
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
};
