// Copyright Epic Games, Inc. All Rights Reserved.

#include "JH_Multi_RPG/Public/Character/JHCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Player/JH_PlayerController.h"
#include "Skill/SkillComponent.h"
#include "Skill/SkillIInfoEnum.h"


DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AJHCharacter::AJHCharacter()
{

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); 

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true; 

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	FollowCamera->bUsePawnControlRotation = false; 

	SkillComponent = CreateDefaultSubobject<USkillComponent>(TEXT("SkillComponet"));
	SkillComponent->SetIsReplicated(true);

}

void AJHCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(IsLocallyControlled() && JH_PlayerController)
	{
		JH_PlayerController->AutoRun();
	}
}

void AJHCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{

		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (IsLocallyControlled())
	{
		JH_PlayerController = Cast<AJH_PlayerController>(Controller);
	}
}

void AJHCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AJHCharacter::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AJHCharacter::MoveReleased);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AJHCharacter::Look);
	
		// 카메라 줌인
		EnhancedInputComponent->BindAction(CameraZoomInAction, ETriggerEvent::Started, this, &AJHCharacter::CameraZoomIn);
		// 카메라 줌아웃
		EnhancedInputComponent->BindAction(CameraZoomOutAction, ETriggerEvent::Started, this, &AJHCharacter::CameraZoomOut);

		// 카메라 자유시점
		EnhancedInputComponent->BindAction(FreeViewAction, ETriggerEvent::Triggered, this, &AJHCharacter::FreeView);
		EnhancedInputComponent->BindAction(FreeViewAction, ETriggerEvent::Completed, this, &AJHCharacter::OriginalView);

		// Skill
		EnhancedInputComponent->BindAction(QSkillAction, ETriggerEvent::Started, this, &AJHCharacter::QSkill);
		EnhancedInputComponent->BindAction(WSkillAction, ETriggerEvent::Started, this, &AJHCharacter::WSkill);
		EnhancedInputComponent->BindAction(ESkillAction, ETriggerEvent::Started, this, &AJHCharacter::ESkill);
		EnhancedInputComponent->BindAction(RSkillAction, ETriggerEvent::Started, this, &AJHCharacter::RSkill);
		EnhancedInputComponent->BindAction(ASkillAction, ETriggerEvent::Started, this, &AJHCharacter::ASkill);
		EnhancedInputComponent->BindAction(SSkillAction, ETriggerEvent::Started, this, &AJHCharacter::SSkill);
		EnhancedInputComponent->BindAction(DSkillAction, ETriggerEvent::Started, this, &AJHCharacter::DSkill);
		EnhancedInputComponent->BindAction(FSkillAction, ETriggerEvent::Started, this, &AJHCharacter::FSkill);

	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AJHCharacter::Move()
{
	if (JH_PlayerController)
	{
		JH_PlayerController->OnTouchTriggered();
	}
}

void AJHCharacter::MoveReleased()
{
	if (JH_PlayerController)
	{
		JH_PlayerController->OnSetDestinationReleased();
	}
}

void AJHCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	if (bIsLeftMouseButtonPressing == false) return;
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AJHCharacter::CameraZoomIn()
{	
	float CurrentFiledOfVie = FollowCamera->FieldOfView;
	FollowCamera->SetFieldOfView(CurrentFiledOfVie - CameraZoomValue);
}

void AJHCharacter::CameraZoomOut()
{
	float CurrentFiledOfVie = FollowCamera->FieldOfView;
	FollowCamera->SetFieldOfView(CurrentFiledOfVie + CameraZoomValue);
}

void AJHCharacter::FreeView()
{
	bIsLeftMouseButtonPressing = true;
}

void AJHCharacter::OriginalView()
{
	bIsLeftMouseButtonPressing = false;
}

void AJHCharacter::QSkill()
{
	SkillComponent->ServerSkill(this,ESkillInput::ESI_InputQ);
}

void AJHCharacter::WSkill()
{
	SkillComponent->ServerSkill(this, ESkillInput::ESI_InputW);
}

void AJHCharacter::ESkill()
{
	SkillComponent->ServerSkill(this, ESkillInput::ESI_InputE);
}

void AJHCharacter::RSkill()
{
	SkillComponent->ServerSkill(this, ESkillInput::ESI_InputR);
}

void AJHCharacter::ASkill()
{
	SkillComponent->ServerSkill(this, ESkillInput::ESI_InputA);
}

void AJHCharacter::SSkill()
{
	SkillComponent->ServerSkill(this, ESkillInput::ESI_InputS);
}

void AJHCharacter::DSkill()
{
	SkillComponent->ServerSkill(this, ESkillInput::ESI_InputD);
}

void AJHCharacter::FSkill()
{
	SkillComponent->ServerSkill(this, ESkillInput::ESI_InputF);
}

