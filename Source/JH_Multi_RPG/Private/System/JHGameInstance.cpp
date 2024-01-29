// Fill out your copyright notice in the Description page of Project Settings.


#include "System/JHGameInstance.h"
#include "UI/Widget/JHUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Save/JHSaveGame.h"

void UJHGameInstance::ShowMainMenu()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (MainMenuWidget == nullptr)
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
	if (CharacterEditorWidget == nullptr)
	{
		CharacterEditorWidget = CreateWidget<UJHUserWidget>(PlayerController, CharacterEditorWidgetClass);
	}
	CharacterEditorWidget->AddToViewport();
	PlayerController->bShowMouseCursor = true;
}

void UJHGameInstance::ShowOptionMesnu()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (CharacterEditorWidget == nullptr)
	{
		OptionWidget = CreateWidget<UJHUserWidget>(PlayerController, OptionWidgetClass);
	}
	OptionWidget->AddToViewport();
	FInputModeUIOnly Mode;
	PlayerController->SetInputMode(Mode);
	PlayerController->bShowMouseCursor = true;
}

void UJHGameInstance::ShowLodingScreen()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (LoadingScreenWidget == nullptr)
	{
		LoadingScreenWidget = CreateWidget<UJHUserWidget>(PlayerController, LoadingWidgetClass);
	}
	LoadingScreenWidget->AddToViewport();
}

void UJHGameInstance::CheckforSavedCharacterInfo()
{
	if (UGameplayStatics::DoesSaveGameExist(PlayerName, 0))
	{
		JHSaveGame = LoadCharacterInfo();
	}
	else
	{
		SaveCharacterInfo();
	}
}

UJHSaveGame* UJHGameInstance::LoadCharacterInfo()
{
	return Cast<UJHSaveGame>(UGameplayStatics::LoadGameFromSlot(PlayerName, 0));
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

