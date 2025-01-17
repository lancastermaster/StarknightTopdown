// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestSystemData.h"
#include "Quest.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectiveIDHeard, FString, ObjectiveID);

UCLASS()
class STARKNIGHTTOPDOWN_API AQuest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuest();

	FName QuestID;
	FQuestDetails QuestDetails;
	int QuestProgress;
	bool IsComplete;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*
	OnObjectiveIDHeard
	GetQuestDetails
	GetObjectiveDataByID
	IsObjectiveComplete
	AreAllObjectivesComplete
	*/


	FQuestDetails GetQuestDetails(FString QuestIdent);
	FObjectiveDetails GetObjectiveDetails(FString ObjectiveID);
	bool IsObjectiveComplete(FString ObjectiveID);
	bool AreAllObjectivesComplete();
private:

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
