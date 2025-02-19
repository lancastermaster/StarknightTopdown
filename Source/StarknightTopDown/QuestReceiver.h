// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestSystemInterface.h"
#include "QuestReceiver.generated.h"

UCLASS()
class STARKNIGHTTOPDOWN_API AQuestReceiver : public AActor, public IQuestSystemInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AQuestReceiver();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ReceiveQuestID(FString QuestID) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Quest System")
	void CallReceived();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
	TArray<FString> Quests;

};
