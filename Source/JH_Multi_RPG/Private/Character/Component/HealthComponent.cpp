// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/HealthComponent.h"
#include "Net/UnrealNetwork.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHealthComponent, Health);
}

void UHealthComponent::IncreaseHealth(float AddHealth)
{
	Health += AddHealth;
	if (Health > MaxHealth)
	{
		Health = MaxHealth;
	}
	OnHeatlhChanged.Broadcast(Health);
}

void UHealthComponent::DecreaseHealth(float MinusHealth)
{
	Health -= MinusHealth;
	if (OnHeatlhChanged.IsBound())
	{
		OnHeatlhChanged.Broadcast(Health);
	}

}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UHealthComponent::OnRep_Health(float OldHealth)
{
	if (OnHeatlhChanged.IsBound())
	{
		OnHeatlhChanged.Broadcast(Health);
	}
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}



