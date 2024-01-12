#pragma once

UENUM(BlueprintType)
enum class EItemType : uint8
{
	EIT_Sword UMETA(DisplayName= "Sword"),
	EIT_Shield UMETA(DisplayName = "Shield"),
	EIT_Potion UMETA(DisplayName = "Potion"),
};