// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "../Character/CharacterInfo/CharacterInfo.h"
#include "JHGameInstance.generated.h"

/**
 * 
 */
class UJHUserWidget;
class UJHSaveGame;

UCLASS()
class JH_MULTI_RPG_API UJHGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void ShowMainMenu();

	UFUNCTION(BlueprintCallable)
	void ShowCharacterEditor();

	UFUNCTION(BlueprintCallable)
	void CheckforSavedCharacterInfo();

	UFUNCTION(BlueprintCallable)
	void LoadCharacterInfo();

	UFUNCTION(BlueprintCallable)
	void SaveCharacterInfo();

	UFUNCTION(BlueprintCallable)
	void ChangePlayerName(FText Name);

	UFUNCTION(BlueprintPure)
	bool CheckPlayerName(const FText& Name);

	UFUNCTION(BlueprintCallable)
	void CreateCharacter(const FText& Name);
protected:

	UPROPERTY()
	TObjectPtr<UJHUserWidget> MainMenuWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UJHUserWidget> MainMenuWidgetClass;

	UPROPERTY()
	TObjectPtr<UJHUserWidget> CharacterEditorWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UJHUserWidget> CharacterEditorWidgetClass;
	
	UPROPERTY(EditAnywhere)
	FString PlayerName = FString();

	UPROPERTY(EditAnywhere)
	FCharacterInfo CharacterInfo;

	UPROPERTY()
	TObjectPtr<UJHSaveGame> JHSaveGame;
};
