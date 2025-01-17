// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "QuestSystemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UQuestSystemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class STARKNIGHTTOPDOWN_API IQuestSystemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Quest")
	virtual void CallQuestID(FString QuestID);

	virtual void ReceiveQuestID(FString QuestID);
};
