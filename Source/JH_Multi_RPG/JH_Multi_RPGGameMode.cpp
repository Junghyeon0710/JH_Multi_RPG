// Copyright Epic Games, Inc. All Rights Reserved.

#include "JH_Multi_RPGGameMode.h"
#include "Character/JHCharacter.h"
#include "UObject/ConstructorHelpers.h"

AJH_Multi_RPGGameMode::AJH_Multi_RPGGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
