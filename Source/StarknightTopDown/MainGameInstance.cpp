// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"
#include "AmmoType.h"
#include "Kismet/GameplayStatics.h"
#include "HealthComponent.h"
#include "WeaponsComponent.h"
#include "PlayerCharacter.h"

void UMainGameInstance::CollectPlayerInfo(float InCurrentHealth, float InMaxHealth, TMap<EAmmoType, int> InCurrentAmmo, TMap<EAmmoType, int> InMaxAmmo, TMap<EAmmoType, bool> InUnlockedWeapons)
{
	PlayerCurrentHealth = InCurrentHealth;
	PlayerMaxHealth = InMaxHealth;
	
	PlayerCurrentAmmo.Empty();
	for (auto& tuple : InCurrentAmmo)
	{
		PlayerCurrentAmmo.Add(tuple.Key, tuple.Value);
	}

	PlayerMaxAmmo.Empty();
	for (auto& tuple : InMaxAmmo)
	{
		PlayerMaxAmmo.Add(tuple.Key, tuple.Value);
	}

	PlayerUnlockedWeapons.Empty();
	for (auto& tuple : InUnlockedWeapons)
	{
		PlayerUnlockedWeapons.Add(tuple.Key, tuple.Value);
	}
}

void UMainGameInstance::DistributePlayerInfo()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	auto HealthComp = Player->GetComponentByClass<UHealthComponent>();

	HealthComp->CurrentHealth = PlayerCurrentHealth;
	HealthComp->MaxHealth = PlayerMaxHealth;

	auto WeaponComp = Player->GetComponentByClass<UWeaponsComponent>();

	for (auto& tuple : PlayerCurrentAmmo)
	{
		WeaponComp->AlterCurrentAmmo(tuple.Key, tuple.Value);
	}

	for (auto& tuple : PlayerMaxAmmo)
	{
		WeaponComp->AlterMaxAmmo(tuple.Key, tuple.Value);
	}

	for (auto& tuple : PlayerUnlockedWeapons)
	{
		WeaponComp->UnlockWeapon(tuple.Key, tuple.Value);
	}
}
