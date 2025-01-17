// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "QuestSystemData.h"
#include "AmmoType.h"
#include "StarknightSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class STARKNIGHTTOPDOWN_API UStarknightSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void CollectPlayerInfo(float InCurrentHealth, float InMaxHealth, float InDamageThreshold, int InSecurityLevel, TMap<EAmmoType, int>InCurrentAmmo, TMap<EAmmoType, int>InMaxAmmo, TMap<EAmmoType, bool>InUnlockedWeapons);

	UFUNCTION(BlueprintCallable)
	void DistributePlayerInfo();
protected:

private:
	FQuestSaveData* PlayerQuestData;

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
	FTransform SaveStationTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World", meta = (AllowPrivateAccess = "true"))
	int SecurityLevel;
};
