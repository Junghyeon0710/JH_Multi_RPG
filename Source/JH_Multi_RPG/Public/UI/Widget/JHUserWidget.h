// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JHUserWidget.generated.h"

/**
 *
 */
UCLASS()
class JH_MULTI_RPG_API UJHUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<UObject> WidgetController; //위젯컨트롤러에 의존할거임
protected:

	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet(); //블루프린트에서 구현
};