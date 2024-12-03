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
	void CollectPlayerInfo(float InCurrentHealth, float InMaxHealth, TMap<EAmmoType, int> InCurrentAmmo, TMap<EAmmoType, int> InMaxAmmo, TMap<EAmmoType, bool> InUnlockedWeapons);

	void DistributePlayerInfo();
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float PlayerCurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float PlayerMaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	TMap<EAmmoType, int>PlayerCurrentAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	TMap<EAmmoType, int>PlayerMaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	TMap<EAmmoType, bool>PlayerUnlockedWeapons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Win Condition", meta = (AllowPrivateAccess = "true"))
	int EggsLeftToDestroy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exploration", meta = (AllowPrivateAccess = "true"))
	int SecurityLevel{0};

public:
	
	UFUNCTION(BlueprintCallable)
	int GetSecurityLevel() { return SecurityLevel; }

	UFUNCTION(BlueprintCallable)
	void SetSecurityLevel(int InSecurityLevel) { SecurityLevel = InSecurityLevel; }
};
