// Fill out your copyright notice in the Description page of Project Settings.


#include "System/JHGameInstance.h"
#include "UI/Widget/JHUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Save/JHSaveGame.h"

void UJHGameInstance::ShowMainMenu()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (MainMenuWidget)
	{
		MainMenuWidget->AddToViewport();
	}
	else
	{
		MainMenuWidget = CreateWidget<UJHUserWidget>(PlayerController, MainMenuWidgetClass);
	}
	MainMenuWidget->AddToViewport();
	FInputModeUIOnly Mode;
	PlayerController->SetInputMode(Mode);
	PlayerController->bShowMouseCursor = true;
}

void UJHGameInstance::ShowCharacterEditor()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (CharacterEditorWidget)
	{
		CharacterEditorWidget->AddToViewport();
	}
	else
	{
		CharacterEditorWidget = CreateWidget<UJHUserWidget>(PlayerController, CharacterEditorWidgetClass);
	}
	CharacterEditorWidget->AddToViewport();
	FInputModeUIOnly Mode;
	PlayerController->SetInputMode(Mode);
	PlayerController->bShowMouseCursor = true;
}

void UJHGameInstance::CheckforSavedCharacterInfo()
{
	if (UGameplayStatics::DoesSaveGameExist(PlayerName, 0))
	{
		LoadCharacterInfo();
	}
	else
	{
		SaveCharacterInfo();
	}
}

void UJHGameInstance::LoadCharacterInfo()
{
	UJHSaveGame* SaveGame = Cast<UJHSaveGame>(UGameplayStatics::LoadGameFromSlot(PlayerName, 0));

	CharacterInfo = SaveGame->CharacterInfo;
}

void UJHGameInstance::SaveCharacterInfo()
{
	if (JHSaveGame == nullptr)
	{
		JHSaveGame = Cast<UJHSaveGame>(UGameplayStatics::CreateSaveGameObject(UJHSaveGame::StaticClass()));
	}
	JHSaveGame->CharacterInfo = CharacterInfo;

	UGameplayStatics::SaveGameToSlot(JHSaveGame, PlayerName, 0);
}

void UJHGameInstance::ChangePlayerName(FText Name)
{
	CharacterInfo.Name = Name;
	SaveCharacterInfo();
}

bool UJHGameInstance::CheckPlayerName(const FText& Name)
{
	if (UGameplayStatics::DoesSaveGameExist(Name.ToString(), 0))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void UJHGameInstance::CreateCharacter(const FText& Name)
{
	if (JHSaveGame == nullptr)
	{
		JHSaveGame = Cast<UJHSaveGame>(UGameplayStatics::CreateSaveGameObject(UJHSaveGame::StaticClass()));
	}

	JHSaveGame->CharacterInfo = CharacterInfo;
	UGameplayStatics::SaveGameToSlot(JHSaveGame, Name.ToString(), 0);
}
