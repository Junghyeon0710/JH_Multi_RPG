// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/JH_PlayerController.h"
#include "Components/SplineComponent.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "UI/JHHUD.h"

AJH_PlayerController::AJH_PlayerController()
{
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
}

void AJH_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController())
	{
		bShowMouseCursor = true; //마우스 커서 보이게함
		
		AJHHUD* JHHUD = Cast<AJHHUD>(GetHUD());
		if (JHHUD)
		{
			JHHUD->InitOverlay(); 
		}
	}
}

void AJH_PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	GetHitResultUnderCursor(ECC_Visibility, false, MouseHitResult);
}

void AJH_PlayerController::OnTouchTriggered()
{
	APawn* ControllerPawn = GetPawn();
	FollowTime += GetWorld()->GetDeltaSeconds(); // 몇초동안 누르고 있었나?
	if (MouseHitResult.bBlockingHit) // 마우스 아래 뭔가 있으면
	{
		CachedDestination = MouseHitResult.ImpactPoint; // 위치를 마우스 히트지점으로 바꿔준다.
	}
	const FVector WorldDirection = (CachedDestination - ControllerPawn->GetActorLocation()).GetSafeNormal();
	ControllerPawn->AddMovementInput(WorldDirection);

	bAutoRunning = false; // 트리거 중이면 AutoRun못하게
}

void AJH_PlayerController::OnSetDestinationReleased()
{
	const APawn* ControllerPawn = GetPawn();
	if (FollowTime <= ShortPressThreshold)
	{
		//포인트를 지워줌
		Spline->ClearSplinePoints();
		/**
		* 내비게이션 시스템에서 특정 위치로 경로를 동기적으로 찾는 함수입니다.
		*이 함수는 주어진 시작 위치에서 목적지 위치까지의 경로를 계산하고 그 결과를 즉시 반환합니다.
		*동기적이라는 것은 함수가 경로를 계산할 때까지 대기한다는 것을 의미합니다.
		*따라서 이 함수가 완료될 때까지 프로그램이 다음 코드로 진행하지 않습니다.
		*/
		if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControllerPawn->GetActorLocation(), CachedDestination))
		{
			for (const FVector& PointLoc : NavPath->PathPoints)
			{
				//스필라인 포인트를 추가시켜줌
				Spline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);

			}
			if (NavPath->PathPoints.Num() > 0)
			{
				//캐릭터 클릭 위치를 마지막 지점으로 해줌
				CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num() - 1];
				// 자동으로 그위치로 감
				bAutoRunning = true;
			}
		}
	}

	FollowTime = 0.f;
}

void AJH_PlayerController::AutoRun()
{
	//클라이언트도 실행하라면 에디터에서 프로젝트 세팅 Nvation System-> Allow Clinet Side Navigation 체크해줘야함
	if (!bAutoRunning) return;
	APawn* ControllerPawn = GetPawn();

	//ControlledPawn의 위치를 기반으로 Spline 상에서 가장 가까운 위치를 찾아 LocationOnSpline에 저장합니다. 
	const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControllerPawn->GetActorLocation(), ESplineCoordinateSpace::World);
	// LocationOnSpline 위치에서 가장 가까운 지점의 방향을 찾아내줌
	const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
	
	//그 방향으로 이동
	ControllerPawn->AddMovementInput(Direction);

	//캐릭터 위치에서 다음 Spline위치 사이 거리
	const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();

	//위치에 도착하면
	if (DistanceToDestination <= AutoRunAcceptanceRadius)
	{
		bAutoRunning = false;
	}

}