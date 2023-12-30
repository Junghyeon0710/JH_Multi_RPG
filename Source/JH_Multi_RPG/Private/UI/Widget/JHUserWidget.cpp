// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/JHUserWidget.h"

void UJHUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController; //위젯컨트롤러 설정

	WidgetControllerSet(); //블루프린트에서 구현합니다.
}