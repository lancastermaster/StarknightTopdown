// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"
#include "AmmoType.h"
#include "Kismet/GameplayStatics.h"
#include "HealthComponent.h"
#include "WeaponsComponent.h"
#include "PlayerCharacter.h"
#include "StarknightSaveGame.h"

void UMainGameInstance::InitializeGame_Implementation()
{
}

void UMainGameInstance::SavePlayerInfo()
{
	SaveGame->CurrentHealth = CurrentHealth;
	SaveGame->MaxHealth = MaxHealth;
	SaveGame->DamageThreshold = DamageThreshold;
	SaveGame->SecurityLevel = SecurityLevel;
	SaveGame->SaveLocation = SaveLocation;
	SaveGame->LevelToOpen = LevelToOpen;

	SaveGame->CurrentAmmo.Empty();
	for (auto tuple : CurrentAmmo)
	{
		SaveGame->CurrentAmmo.Add(tuple.Key, tuple.Value);
	}

	SaveGame->MaxAmmo.Empty();
	for (auto tuple : MaxAmmo)
	{
		SaveGame->MaxAmmo.Add(tuple.Key, tuple.Value);
	}

	SaveGame->UnlockedWeapons.Empty();
	for (auto tuple : UnlockedWeapons)
	{
		SaveGame->UnlockedWeapons.Add(tuple.Key, tuple.Value);
	}
}

void UMainGameInstance::LoadPlayerInfo()
{
	CurrentHealth = SaveGame->CurrentHealth;
	MaxHealth = SaveGame->MaxHealth;
	DamageThreshold = SaveGame->DamageThreshold;
	SecurityLevel = SaveGame->SecurityLevel;
	SaveLocation = SaveGame->SaveLocation;
	LevelToOpen = SaveGame->LevelToOpen;

	CurrentAmmo.Empty();
	for (auto tuple : SaveGame->CurrentAmmo)
	{
		CurrentAmmo.Add(tuple.Key, tuple.Value);
	}

	MaxAmmo.Empty();
	for (auto tuple : SaveGame->MaxAmmo)
	{
		MaxAmmo.Add(tuple.Key, tuple.Value);
	}

	UnlockedWeapons.Empty();
	for (auto tuple : SaveGame->UnlockedWeapons)
	{
		UnlockedWeapons.Add(tuple.Key, tuple.Value);
	}
}
