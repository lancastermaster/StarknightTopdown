// Fill out your copyright notice in the Description page of Project Settings.


#include "StarknightSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"
#include "HealthComponent.h"
#include "WeaponsComponent.h"
#include "MainGameInstance.h"

void UStarknightSaveGame::CollectPlayerInfo()
{
	UMainGameInstance* Instance = Cast<UMainGameInstance>(UGameplayStatics::GetGameInstance(this));
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	Player->CollectPlayerSaveInfo();

	//FPlayerSaveInfo InfoToSave = Player->GetPlayerSaveInfo();

	CurrentHealth = Instance->CurrentHealth;
	MaxHealth = Instance->MaxHealth;
	DamageThreshold = Instance->DamageThreshold;
	SecurityLevel = Instance->SecurityLevel;

	CurrentAmmo.Empty();
	for (auto tuple : Instance->CurrentAmmo)
	{
		CurrentAmmo.Add(tuple.Key, tuple.Value);
	}

	MaxAmmo.Empty();
	for (auto tuple : Instance->MaxAmmo)
	{
		MaxAmmo.Add(tuple.Key, tuple.Value);
	}

	UnlockedWeapons.Empty();
	for (auto tuple : Instance->UnlockedWeapons)
	{
		UnlockedWeapons.Add(tuple.Key, tuple.Value);
	}
}

void UStarknightSaveGame::DistributePlayerInfo()
{
	UMainGameInstance* Instance = Cast<UMainGameInstance>(UGameplayStatics::GetGameInstance(this));

	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	Instance->CurrentHealth = CurrentHealth;
	Instance->MaxHealth = MaxHealth;

	for (auto& tuple : CurrentAmmo)
	{
		Instance->CurrentAmmo.Add(tuple.Key, tuple.Value);
	}

	for (auto& tuple : MaxAmmo)
	{
		Instance->MaxAmmo.Add(tuple.Key, tuple.Value);
	}

	for (auto& tuple : UnlockedWeapons)
	{
		Instance->UnlockedWeapons.Add(tuple.Key, tuple.Value);
	}

	Player->LoadPlayerInfo();
}
