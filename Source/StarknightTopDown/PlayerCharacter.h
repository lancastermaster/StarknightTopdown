// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmmoType.h"
#include "HumanoidCharacter.h"
#include "InputAction.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class STARKNIGHTTOPDOWN_API APlayerCharacter : public AHumanoidCharacter
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	class UHealthComponent* HealthComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	class UWeaponsComponent* WeaponComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	class UInteractorComponent* InteractorComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	class UStatusEffectComponent* StatusComp;

protected:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	virtual void Tick(float DeltaTime) override;

	void Move(const FInputActionValue& AxisValue);
	void Look();

	void Interact();
	void PrimaryAction();
	void SecondaryAction();

	void EquipAssaultRifle();
	void EquipShotgun();
	void EquipQuaker();
	void ResetCanTakeDamage();

	UFUNCTION(BlueprintNativeEvent)
	void HurtEffect();

	UFUNCTION(BlueprintNativeEvent)
	void OnDeath();
	//void SetWeaponProperties(FWeaponInfo InEquippedWeapon);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* CombatMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* PrimaryInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* SecondaryInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* DashAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* Hotkey1Action;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* Hotkey2Action;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* Hotkey3Action;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* ScrollWheelAction;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	bool bPrimaryDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	bool bSecondaryDown;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	bool bPlayerIsDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float DamageKnockback {10000.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float HurtReactTime{ 3.f };

	bool bInvulnerable = false;

	FTimerHandle HurtHandle;
	/*
	gameInstance reference
	animMontages
	*/
public:
	APlayerCharacter();


	void SetPrimaryDown(const FInputActionValue& KeyValue);
	void SetSecondaryDown(const FInputActionValue& KeyValue);

	FORCEINLINE bool GetPlayerIsDead() { return bPlayerIsDead; }
};
