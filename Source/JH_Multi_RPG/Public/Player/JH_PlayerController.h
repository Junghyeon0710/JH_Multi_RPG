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
	
	void OnSetDestinationReleased(); // 목적지 설정
	void OnTouchTriggered(); // 마우스 계속 클릭중
	void AutoRun(); // 자동으로 목적지까지 감
private:
	FHitResult MouseHitResult;

	/** 캐릭터 클릭 위치*/
	FVector CachedDestination = FVector::ZeroVector;
	/** 얼마나 눌렀는지*/
	float FollowTime = 0.f;
	/** 얼마나 짧게 눌렀는지 기준점*/
	float ShortPressThreshold = 0.5f;
	/** 언제 자동으로 움직여야하는지*/
	bool bAutoRunning = false;
	/** 얼마큼 와야 자동움직임 멈추는지*/
	float AutoRunAcceptanceRadius = 50.f;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;

public:
	FORCEINLINE FHitResult GetMouseHitReulst() const { return MouseHitResult; }
};
