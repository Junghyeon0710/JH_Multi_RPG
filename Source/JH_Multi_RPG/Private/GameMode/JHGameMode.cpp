// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/JHGameMode.h"
#include "Character/JHCharacter.h"

void AJHGameMode::CharacterJoin(AJHCharacter* Player,const FCharacterInfo& PlayerInfo)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Server%d"), Player));
	PlayerCharacters.Add(Player);
	PlayerCharacterInfos.Add(PlayerInfo);
}

void AJHGameMode::UpdateAllCharacter()
{
	int32 Index = 0;
	for (const auto& Player : PlayerCharacters)
	{
		Player.Get()->MultiUpdateAllCharacter(Player, PlayerCharacterInfos[Index]);
		Index++;
	}
}
