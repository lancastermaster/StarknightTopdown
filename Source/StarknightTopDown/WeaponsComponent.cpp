// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponsComponent.h"
#include "AmmoType.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/DamageType.h"
#include "Engine/DataTable.h"
#include "Engine/EngineTypes.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "HealthComponent.h"
#include "Math/UnrealMathUtility.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Projectile.h"
#include "Sound/SoundBase.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UWeaponsComponent::UWeaponsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	MaxAmmo.Add(EAmmoType::EAT_AR, 200);
	MaxAmmo.Add(EAmmoType::EAT_Buckshot, 40);
	MaxAmmo.Add(EAmmoType::EAT_ThunderRound, 8);

	UnlockedWeapons.Add(EAmmoType::EAT_AR, true);
	UnlockedWeapons.Add(EAmmoType::EAT_Buckshot, false);
	UnlockedWeapons.Add(EAmmoType::EAT_ThunderRound, false);
}


// Called when the game starts
void UWeaponsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UWeaponsComponent::FireEquippedWeapon(UStaticMeshComponent* InWeaponMesh, FVector CursorLocation)
{
	if (!bCanBeFired)return;
	if (!InWeaponMesh)return;
	if (!CurrentAmmo.Contains(EquippedWeapon.WeaponAmmoType))return;

	if (CurrentAmmo.Find(EquippedWeapon.WeaponAmmoType) > 0)
	{
		//set bCanBeFired to false
		//play gunfire sound
		//spawn muzzleflash particles
	
		bCanBeFired = false;

		if(EquippedWeapon.WeaponFireSound)
		UGameplayStatics::SpawnSoundAtLocation(
			GetWorld(), 
			EquippedWeapon.WeaponFireSound, 
			InWeaponMesh->GetSocketLocation(FName("Barrel")),
			InWeaponMesh->GetSocketRotation(FName("Barrel"))
		);

		if(EquippedWeapon.WeaponMuzzleFlash)
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			EquippedWeapon.WeaponMuzzleFlash,
			InWeaponMesh->GetSocketLocation(FName("Barrel")),
			InWeaponMesh->GetSocketRotation(FName("Barrel"))
			);

		switch (EquippedWeapon.WeaponAmmoType)
		{
			case EAmmoType::EAT_AR:
				FireRaycast(InWeaponMesh,0.f);
			break;

			case EAmmoType::EAT_Buckshot:
			{
				int i = 0;
				while (i < 10)
				{
					FireRaycast(InWeaponMesh,10.f);
					i++;
				}
			}
			break;


			case EAmmoType::EAT_ThunderRound:
				//Spawns projectile in the given direction

				if (EquippedWeapon.ProjectileClass)
				{
					AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(EquippedWeapon.ProjectileClass, InWeaponMesh->GetSocketLocation(FName("Barrel")), InWeaponMesh->GetSocketRotation(FName("Barrel")));
					Projectile->SetOwner(GetOwner());
					Projectile->Damage = EquippedWeapon.WeaponDamage;
					Projectile->WeaponDamageType = EquippedWeapon.WeaponDamageType;
				}
			break;

			case EAmmoType::EAT_Plasma:
				if (EquippedWeapon.ProjectileClass)
				{
					AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(EquippedWeapon.ProjectileClass, InWeaponMesh->GetSocketLocation(FName("Barrel")), InWeaponMesh->GetSocketRotation(FName("Barrel")));
					Projectile->SetOwner(GetOwner());
					Projectile->Damage = EquippedWeapon.WeaponDamage;
					Projectile->WeaponDamageType = EquippedWeapon.WeaponDamageType;
				}
				break;

			case EAmmoType::EAT_Voltaic:
				//Spawns projectile in the given direction

				if (EquippedWeapon.ProjectileClass)
				{
					AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(EquippedWeapon.ProjectileClass, InWeaponMesh->GetSocketLocation(FName("Barrel")), InWeaponMesh->GetSocketRotation(FName("Barrel")));
					Projectile->SetOwner(GetOwner());
					Projectile->Damage = EquippedWeapon.WeaponDamage;
					Projectile->WeaponDamageType = EquippedWeapon.WeaponDamageType;
				}
				break;
		}
	}


	if(EquippedWeapon.WeaponAmmoType != EAmmoType::EAT_Plasma)AlterCurrentAmmo(EquippedWeapon.WeaponAmmoType, -1);
	//AlterCurrentAmmo(EquippedWeapon.WeaponAmmoType, -1);

	FTimerHandle FireTimer;

	GetWorld()->GetTimerManager().SetTimer(FireTimer, this, &UWeaponsComponent::ResetCanBeFired, EquippedWeapon.WeaponDelay);

	//set timer to reset bCanBeFired
}

void UWeaponsComponent::ResetCanBeFired()
{
	bCanBeFired = true;
}

void UWeaponsComponent::FireRaycast(UStaticMeshComponent* InWeaponMesh, float BarrelYawMod)
{
	if (!InWeaponMesh)return;
	//linetrace towards cursor
	FHitResult RifleHit;

	FVector BulletSpawn = InWeaponMesh->GetSocketLocation(FName("Barrel"));
	//FRotator BarrelRotation = InWeaponMesh->GetSocketRotation(FName("Barrel"));
	FRotator BarrelRotation = InWeaponMesh->GetForwardVector().Rotation();

	if (BarrelYawMod > 0.f)
	{
		BarrelRotation.Yaw += (FMath::FRandRange(-BarrelYawMod, BarrelYawMod));
	}

	GetWorld()->LineTraceSingleByChannel(RifleHit, BulletSpawn, BulletSpawn + BarrelRotation.Vector() * 15000, ECollisionChannel::ECC_Visibility);

	if (RifleHit.bBlockingHit)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), EquippedWeapon.WeaponImpact, RifleHit.Location);
		UGameplayStatics::ApplyDamage(RifleHit.GetActor(), EquippedWeapon.WeaponDamage, GetOwner()->GetInstigatorController(), GetOwner(), EquippedWeapon.WeaponDamageType);

		/*UHealthComponent* HitHealthComp = RifleHit.GetActor()->GetComponentByClass<UHealthComponent>();
		if (HitHealthComp)
		{
			UGameplayStatics::ApplyDamage(RifleHit.GetActor(), EquippedWeapon.WeaponDamage, GetOwner()->GetInstigatorController(), GetOwner(), UDamageType::StaticClass());
		}*/
	}
	//spawn beam effect
	//spawn hit particles at hit location
	//deal damage to hit actor, if any
}

void UWeaponsComponent::EquipWeapon(FName InWeaponName)
{
	FWeaponInfoDataTable* RowInfo = WeaponDataTable->FindRow<FWeaponInfoDataTable>(InWeaponName,FString(""));
	if (RowInfo)
	{
		EquippedWeapon.AmmoIcon = RowInfo->AmmoIcon;
		EquippedWeapon.ProjectileClass = RowInfo->ProjectileClass;
		EquippedWeapon.WeaponAmmoType = RowInfo->WeaponAmmoType;
		EquippedWeapon.WeaponBeam = RowInfo->WeaponBeam;
		EquippedWeapon.WeaponCrosshair = RowInfo->WeaponCrosshair;
		EquippedWeapon.WeaponDamage = RowInfo->WeaponDamage;
		EquippedWeapon.WeaponDelay = RowInfo->WeaponDelay;
		EquippedWeapon.WeaponFireSound = RowInfo->WeaponFireSound;
		EquippedWeapon.WeaponHitSound = RowInfo->WeaponHitSound;
		EquippedWeapon.WeaponIcon = RowInfo->WeaponIcon;
		EquippedWeapon.WeaponImpact = RowInfo->WeaponImpact;
		EquippedWeapon.WeaponMesh = RowInfo->WeaponMesh;
		EquippedWeapon.WeaponMuzzleFlash = RowInfo->WeaponMuzzleFlash;
		EquippedWeapon.WeaponName = RowInfo->WeaponName;
		EquippedWeapon.WeaponDamageType = RowInfo->WeaponDamageType;
	}
}

void UWeaponsComponent::AlterCurrentAmmo(EAmmoType WeaponAmmoType, int ChangeAmount)
{
	int AlteredAmmo = HasAmmo(WeaponAmmoType) + ChangeAmount;

	CurrentAmmo.Add(WeaponAmmoType, AlteredAmmo);
}

void UWeaponsComponent::AlterMaxAmmo(EAmmoType WeaponAmmoType, int ChangeAmount)
{
	int AlteredMax = QueryMaxAmmo(WeaponAmmoType) + ChangeAmount;

	MaxAmmo.Add(WeaponAmmoType, AlteredMax);
}

// Called every frame
void UWeaponsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

