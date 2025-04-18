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
USTRUCT(BlueprintType)
struct FPlayerSaveInfo 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float DamageThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	TMap<EAmmoType, int>CurrentAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	TMap<EAmmoType, int>MaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	TMap<EAmmoType, bool>UnlockedWeapons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World", meta = (AllowPrivateAccess = "true"))
	FName LevelToOpen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World", meta = (AllowPrivateAccess = "true"))
	FVector SaveLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World", meta = (AllowPrivateAccess = "true"))
	int SecurityLevel;
};

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quests", meta = (AllowPrivateAccess = "true"))
	class UQuestLogComponent* QuestLog;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	class UPointLightComponent* ChargingLight;

protected:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	virtual void Tick(float DeltaTime) override;

	void Move(const FInputActionValue& AxisValue);
	void Look();

	void Interact();
	void Dash();
	void PrimaryAction();
	void SecondaryAction();

	void EquipPlasmaGun();
	void EquipLightningGun();
	void EquipQuaker();
	void ResetCanTakeDamage();

	UFUNCTION(BlueprintNativeEvent)
	void HurtEffect();

	UFUNCTION(BlueprintNativeEvent)
	void OnDeath();
	//void SetWeaponProperties(FWeaponInfo InEquippedWeapon);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


private:

	//Player Input
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
	
	float CurrentChargeAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	bool bPlayerIsDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float DamageKnockback {10000.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float HurtReactTime{ 3.f };

	//VFX
	class UNiagaraComponent* ChargeEffect;

	//SFX
	class UAudioComponent* ChargeSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrades", meta = (AllowPrivateAccess = "true"))
	TMap<FString, bool> Powerups;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exploration", meta = (AllowPrivateAccess = "true"))
	int SecurityLevel{ 0 };

	bool bInvulnerable = false;

	FTimerHandle HurtHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveInfo", meta = (AllowPrivateAccess = "true"))
	struct FPlayerSaveInfo PlayerInfo;
	/*
	animMontages
	*/

	class UMainGameInstance* GameInstance;

	//UI
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> HUDClass;
	UUserWidget* HUD;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> GameOverScreenClass;
	UUserWidget* GameOverScreen;*/

public:
	APlayerCharacter();


	void SetPrimaryDown(const FInputActionValue& KeyValue);
	void SetSecondaryDown(const FInputActionValue& KeyValue);

	UFUNCTION(BlueprintCallable)
	int GetSecurityLevel() { return SecurityLevel; }

	UFUNCTION(BlueprintCallable)
	void SetSecurityLevel(int InSecurityLevel) { SecurityLevel = InSecurityLevel; }

	FORCEINLINE bool GetPlayerIsDead() { return bPlayerIsDead; }

	UFUNCTION(BlueprintCallable)
	void CollectPlayerSaveInfo();

	UFUNCTION(BlueprintCallable)
	void LoadPlayerInfo();
};
