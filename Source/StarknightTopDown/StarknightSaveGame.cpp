// Fill out your copyright notice in the Description page of Project Settings.


#include "StarknightSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"
#include "HealthComponent.h"
#include "WeaponsComponent.h"

void UStarknightSaveGame::CollectPlayerInfo()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	//Player->CollectPlayerSaveInfo();

	FPlayerSaveInfo InfoToSave = Player->GetPlayerSaveInfo();

	CurrentHealth = InfoToSave.CurrentHealth;
	MaxHealth = InfoToSave.MaxHealth;
	DamageThreshold = InfoToSave.DamageThreshold;
	SecurityLevel = InfoToSave.SecurityLevel;

	CurrentAmmo.Empty();
	for (auto tuple : InfoToSave.CurrentAmmo)
	{
		CurrentAmmo.Add(tuple.Key, tuple.Value);
	}

	MaxAmmo.Empty();
	for (auto tuple : InfoToSave.MaxAmmo)
	{
		MaxAmmo.Add(tuple.Key, tuple.Value);
	}

	UnlockedWeapons.Empty();
	for (auto tuple : InfoToSave.UnlockedWeapons)
	{
		UnlockedWeapons.Add(tuple.Key, tuple.Value);
	}
}

void UStarknightSaveGame::DistributePlayerInfo()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	auto HealthComp = Player->GetComponentByClass<UHealthComponent>();
	auto WeaponComp = Player->GetComponentByClass<UWeaponsComponent>();

	HealthComp->CurrentHealth = CurrentHealth;
	HealthComp->MaxHealth = MaxHealth;

	for (auto& tuple : CurrentAmmo)
	{
		WeaponComp->AlterCurrentAmmo(tuple.Key, tuple.Value);
	}

	for (auto& tuple : MaxAmmo)
	{
		WeaponComp->AlterMaxAmmo(tuple.Key, tuple.Value);
	}

	for (auto& tuple : UnlockedWeapons)
	{
		WeaponComp->UnlockWeapon(tuple.Key, tuple.Value);
	}
}
