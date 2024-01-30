// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "../Interfaces/InventoryInterface.h"
#include "CharacterInfo/CharacterInfo.h"
#include "JHCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class AJH_PlayerController;
class USkillComponent;
class UJHInventoryComponent;
class UHealthComponent;
class USceneCaptureComponent2D;
class UMaterialInterface;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AJHCharacter : public ACharacter , public IInventoryInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** InventoryContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* InventoryContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** ī�޶� Ȯ�� �׼� */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* CameraZoomInAction;

	/** ī�Ŷ� ��� �׼� */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* CameraZoomOutAction;

	/** ĳ���� ���� �׼� */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FreeViewAction;

	/** Q��ų �׼� */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* QSkillAction;

	/** W��ų �׼� */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* WSkillAction;

	/** E��ų �׼� */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ESkillAction;

	/** R��ų �׼� */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RSkillAction;

	/** A��ų �׼� */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ASkillAction;

	/** S��ų �׼� */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SSkillAction;

	/** D��ų �׼� */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* DSkillAction;

	/** F��ų �׼� */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FSkillAction;

	/** I �κ��丮 �׼� */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InventoryAction;

	/** I �κ��丮 �׼� */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PickupItemAction;

public:
	AJHCharacter();
	virtual void Tick(float DeltaTime) override;

	/** InventoryInterface*/

	virtual void AddItem_Implementation(AMasterItem* Item) override;
	virtual void AddGold_Implementation(AMasterItem* Item) override;
	virtual void SetSword_Implementation(UStaticMesh* SwordMesh) override;
	virtual void SetShield_Implementation(UStaticMesh* ShieldMesh) override;

	/** /InventoryInterface*/

	//virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const override;

	UPROPERTY()
	FCharacterInfo CharacterInfo;

	UFUNCTION(Server,Reliable)
	void ServerJoinCharacter(AJHCharacter* Player, const FCharacterInfo& Info);

	UFUNCTION(NetMulticast, Reliable)
	void MultiUpdateAllCharacter(AJHCharacter* Player, const FCharacterInfo& PlayerInfo);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	/** Called for movement input */
	void Move();
	void MoveReleased();

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** ī�޶����� �ݹ��Լ�*/
	void CameraZoomIn();

	/** ī�޶��ܾƿ� �ݹ��Լ�*/
	void CameraZoomOut();

	/** �������� �ݹ��Լ�*/
	void FreeView();

	/** �������� �ݹ��Լ�*/
	void OriginalView();
			
	/** Skills*/
	void QSkill();
	void WSkill();
	void ESkill();
	void RSkill();
	void ASkill();
	void SSkill();
	void DSkill();
	void FSkill();

	/** �κ��丮 */
	void InventoryKeyPress();

	/** ������ �ݱ�*/
	void PickupItem();
private:

	/** ī�޶� �� �� �ٿ� ��*/
	UPROPERTY(EditDefaultsOnly,Category = "Camera")
	float CameraZoomValue = 5;

	/** ��ƮŰ�� ������ ��*/
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	bool bIsLeftMouseButtonPressing = false;

	UPROPERTY()
	TObjectPtr<AJH_PlayerController> JH_PlayerController;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkillComponent> SkillComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UJHInventoryComponent> JHInventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly ,meta =(AllowPrivateAccess = "true"))
	TObjectPtr<UHealthComponent> HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneCaptureComponent2D> SceneCaptureComponent2D;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Sword;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Shield;

	

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE class USkillComponent* GetSKillComponent() const { return SkillComponent; }
	FORCEINLINE class UJHInventoryComponent* GetInventoryComponent() const { return JHInventoryComponent; }
	FORCEINLINE class UHealthComponent* GetHealthComponent() const { return HealthComponent; }
};

