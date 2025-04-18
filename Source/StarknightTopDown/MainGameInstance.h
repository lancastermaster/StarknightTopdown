// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AmmoType.h"
#include "MainGameInstance.generated.h"

/**
 * 
 */

UCLASS()
class STARKNIGHTTOPDOWN_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	

protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InitializeGame();

	UFUNCTION(BlueprintCallable)
	void SavePlayerInfo();

	UFUNCTION(BlueprintCallable)
	void LoadPlayerInfo();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Game", meta = (AllowPrivateAccess = "true"))
	class UStarknightSaveGame* SaveGame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Game", meta = (AllowPrivateAccess = "true"))
	FString FileName;

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UStarknightSaveGame* GetSaveGame() { return SaveGame; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE FString GetSaveFileName() { return FileName; }

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
	int SecurityLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World", meta = (AllowPrivateAccess = "true"))
	FName LevelToOpen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World", meta = (AllowPrivateAccess = "true"))
	FVector SaveLocation;
};
