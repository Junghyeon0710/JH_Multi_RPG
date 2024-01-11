// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "../Interfaces/InventoryInterface.h"
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

	/** 카메라 확대 액션 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* CameraZoomInAction;

	/** 카매라 축소 액션 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* CameraZoomOutAction;

	/** 캐릭터 시점 액션 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FreeViewAction;

	/** Q스킬 액션 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* QSkillAction;

	/** W스킬 액션 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* WSkillAction;

	/** E스킬 액션 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ESkillAction;

	/** R스킬 액션 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RSkillAction;

	/** A스킬 액션 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ASkillAction;

	/** S스킬 액션 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SSkillAction;

	/** D스킬 액션 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* DSkillAction;

	/** F스킬 액션 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FSkillAction;

	/** I 인벤토리 액션 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InventoryAction;

public:
	AJHCharacter();
	virtual void Tick(float DeltaTime) override;

	/** InventoryInterface*/

	virtual void AddItem_Implementation(AMasterItem* Item) override;
	virtual void AddGold_Implementation(AMasterItem* Item) override;

	/** /InventoryInterface*/

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

	/** 카메라줌인 콜백함수*/
	void CameraZoomIn();

	/** 카메라줌아웃 콜백함수*/
	void CameraZoomOut();

	/** 자유시점 콜백함수*/
	void FreeView();

	/** 원래시점 콜백함수*/
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

	/** 인벤토리 */
	void InventoryKeyPress();
private:

	/** 카메라 줌 업 다운 값*/
	UPROPERTY(EditDefaultsOnly,Category = "Camera")
	float CameraZoomValue = 5;

	/** 알트키를 눌렀는 가*/
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
	

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE class USkillComponent* GetSKillComponent() const { return SkillComponent; }
	FORCEINLINE class UJHInventoryComponent* GetInventoryComponent() const { return JHInventoryComponent; }
	FORCEINLINE class UHealthComponent* GetHealthComponent() const { return HealthComponent; }
};

