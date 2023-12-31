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
	/**�� ������ ���� ��Ʈ�ѷ� �������ݴϴ�. */
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<UObject> WidgetController; //������Ʈ�ѷ��� �����Ұ���
protected:

	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet(); //�������Ʈ���� ����
};