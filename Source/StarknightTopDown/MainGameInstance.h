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
	UFUNCTION(BlueprintNativeEvent)
	void InitializeGame();

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
};
