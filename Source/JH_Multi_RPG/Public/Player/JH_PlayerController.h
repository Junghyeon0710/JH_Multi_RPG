// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "JH_PlayerController.generated.h"


class USplineComponent;

/**
 * 
 */
UCLASS()
class JH_MULTI_RPG_API AJH_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	AJH_PlayerController();

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

public:
	virtual void PlayerTick(float DeltaTime) override;
	
	void OnSetDestinationReleased(); // ������ ����
	void OnTouchTriggered(); // ���콺 ��� Ŭ����
	void AutoRun(); // �ڵ����� ���������� ��
private:
	FHitResult MouseHitResult;

	/** ĳ���� Ŭ�� ��ġ*/
	FVector CachedDestination = FVector::ZeroVector;
	/** �󸶳� ��������*/
	float FollowTime = 0.f;
	/** �󸶳� ª�� �������� ������*/
	float ShortPressThreshold = 0.5f;
	/** ���� �ڵ����� ���������ϴ���*/
	bool bAutoRunning = false;
	/** ��ŭ �;� �ڵ������� ���ߴ���*/
	float AutoRunAcceptanceRadius = 50.f;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;

public:
	FORCEINLINE FHitResult GetMouseHitReulst() const { return MouseHitResult; }
};
