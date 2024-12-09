// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AmmoType.h"
#include "Engine/DataTable.h"
#include "WeaponsComponent.generated.h"

USTRUCT(BlueprintType)
struct FWeaponInfoDataTable : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info", meta = (AllowPrivateAccess = "true"))
	FName WeaponName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info", meta = (AllowPrivateAccess = "true"))
	EAmmoType WeaponAmmoType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info", meta = (AllowPrivateAccess = "true"))
	float WeaponDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info", meta = (AllowPrivateAccess = "true"))
	float WeaponDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info", meta = (AllowPrivateAccess = "true"))
	class UTexture2D* WeaponIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info", meta = (AllowPrivateAccess = "true"))
	UTexture2D* WeaponCrosshair;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info", meta = (AllowPrivateAccess = "true"))
	UTexture2D* AmmoIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info", meta = (AllowPrivateAccess = "true"))
	class USoundBase* WeaponFireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info", meta = (AllowPrivateAccess = "true"))
	USoundBase* WeaponHitSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info", meta = (AllowPrivateAccess = "true"))
	class UNiagaraSystem* WeaponMuzzleFlash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info", meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem* WeaponImpact;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info", meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem* WeaponBeam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info", meta = (AllowPrivateAccess = "true"))
	class UStaticMesh* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectile> ChargedProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UDamageType> WeaponDamageType;
};

USTRUCT(BlueprintType)
struct FWeaponInfo {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info", meta = (AllowPrivateAccess = "true"))
	FName WeaponName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info", meta = (AllowPrivateAccess = "true"))
	EAmmoType WeaponAmmoType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info", meta = (AllowPrivateAccess = "true"))
	float WeaponDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info", meta = (AllowPrivateAccess = "true"))
	float WeaponDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info", meta = (AllowPrivateAccess = "true"))
	class UTexture2D* WeaponIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info", meta = (AllowPrivateAccess = "true"))
	UTexture2D* WeaponCrosshair;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info", meta = (AllowPrivateAccess = "true"))
	UTexture2D* AmmoIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info", meta = (AllowPrivateAccess = "true"))
	class USoundBase* WeaponFireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info", meta = (AllowPrivateAccess = "true"))
	USoundBase* WeaponHitSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info", meta = (AllowPrivateAccess = "true"))
	class UNiagaraSystem* WeaponMuzzleFlash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info", meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem* WeaponImpact;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info", meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem* WeaponBeam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info", meta = (AllowPrivateAccess = "true"))
	UStaticMesh* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectile> ChargedProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UDamageType> WeaponDamageType;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STARKNIGHTTOPDOWN_API UWeaponsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponsComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info", meta = (AllowPrivateAccess = "true"))
	FWeaponInfo EquippedWeapon;

	FTimerHandle ShootTimer;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	TMap<EAmmoType, int>CurrentAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	TMap<EAmmoType, int>MaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	TMap<EAmmoType, bool>UnlockedWeapons;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Info", meta = (AllowPrivateAccess = "true"))
	UDataTable* WeaponDataTable;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info", meta = (AllowPrivateAccess = "true"))
	bool bCanBeFired;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void FireEquippedWeapon(UStaticMeshComponent* InWeaponMesh, FVector CursorLocation);

	void FireSecondary(UStaticMeshComponent* InWeaponMesh, FVector CursorLocation);

	void ResetCanBeFired();

	void FireRaycast(UStaticMeshComponent* InWeaponMesh, float BarrelYawMod);

	void EquipWeapon(FName InWeaponName);
	
	UFUNCTION(BlueprintCallable)
	int HasAmmo(EAmmoType WeaponAmmoType) { return CurrentAmmo[WeaponAmmoType]; }

	int QueryMaxAmmo(EAmmoType WeaponAmmoType) { return MaxAmmo[WeaponAmmoType]; }

	UFUNCTION(BlueprintCallable)
	void AlterCurrentAmmo(EAmmoType WeaponAmmoType, int ChangeAmount);

	void AlterMaxAmmo(EAmmoType WeaponAmmoType, int ChangeAmount);

	void UnlockWeapon(EAmmoType Weapon, bool bUnlock) { UnlockedWeapons.Add(Weapon, bUnlock); }

	bool QueryWeapons(EAmmoType Weapon) { return UnlockedWeapons[Weapon]; }

	bool GetCanBeFired() { return bCanBeFired; }

	//bool GetBeamEndLocation(const FVector& BulletSpawnLocation, FHitResult& OutHitResult);
		
};
