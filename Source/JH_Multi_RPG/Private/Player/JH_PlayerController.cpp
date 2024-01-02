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
		bShowMouseCursor = true; //���콺 Ŀ�� ���̰���
		
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
	FollowTime += GetWorld()->GetDeltaSeconds(); // ���ʵ��� ������ �־���?
	if (MouseHitResult.bBlockingHit) // ���콺 �Ʒ� ���� ������
	{
		CachedDestination = MouseHitResult.ImpactPoint; // ��ġ�� ���콺 ��Ʈ�������� �ٲ��ش�.
	}
	const FVector WorldDirection = (CachedDestination - ControllerPawn->GetActorLocation()).GetSafeNormal();
	ControllerPawn->AddMovementInput(WorldDirection);

	bAutoRunning = false; // Ʈ���� ���̸� AutoRun���ϰ�
}

void AJH_PlayerController::OnSetDestinationReleased()
{
	const APawn* ControllerPawn = GetPawn();
	if (FollowTime <= ShortPressThreshold)
	{
		//����Ʈ�� ������
		Spline->ClearSplinePoints();
		/**
		* ������̼� �ý��ۿ��� Ư�� ��ġ�� ��θ� ���������� ã�� �Լ��Դϴ�.
		*�� �Լ��� �־��� ���� ��ġ���� ������ ��ġ������ ��θ� ����ϰ� �� ����� ��� ��ȯ�մϴ�.
		*�������̶�� ���� �Լ��� ��θ� ����� ������ ����Ѵٴ� ���� �ǹ��մϴ�.
		*���� �� �Լ��� �Ϸ�� ������ ���α׷��� ���� �ڵ�� �������� �ʽ��ϴ�.
		*/
		if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControllerPawn->GetActorLocation(), CachedDestination))
		{
			for (const FVector& PointLoc : NavPath->PathPoints)
			{
				//���ʶ��� ����Ʈ�� �߰�������
				Spline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);

			}
			if (NavPath->PathPoints.Num() > 0)
			{
				//ĳ���� Ŭ�� ��ġ�� ������ �������� ����
				CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num() - 1];
				// �ڵ����� ����ġ�� ��
				bAutoRunning = true;
			}
		}
	}

	FollowTime = 0.f;
}

void AJH_PlayerController::AutoRun()
{
	//Ŭ���̾�Ʈ�� �����϶�� �����Ϳ��� ������Ʈ ���� Nvation System-> Allow Clinet Side Navigation üũ�������
	if (!bAutoRunning) return;
	APawn* ControllerPawn = GetPawn();

	//ControlledPawn�� ��ġ�� ������� Spline �󿡼� ���� ����� ��ġ�� ã�� LocationOnSpline�� �����մϴ�. 
	const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControllerPawn->GetActorLocation(), ESplineCoordinateSpace::World);
	// LocationOnSpline ��ġ���� ���� ����� ������ ������ ã�Ƴ���
	const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
	
	//�� �������� �̵�
	ControllerPawn->AddMovementInput(Direction);

	//ĳ���� ��ġ���� ���� Spline��ġ ���� �Ÿ�
	const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();

	//��ġ�� �����ϸ�
	if (DistanceToDestination <= AutoRunAcceptanceRadius)
	{
		bAutoRunning = false;
	}

}