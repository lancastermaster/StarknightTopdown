// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest.h"
#include "QuestSystemData.h"

// Sets default values
AQuest::AQuest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// Called when the game starts or when spawned
void AQuest::BeginPlay()
{
	Super::BeginPlay();
	
}

FQuestDetails AQuest::GetQuestDetails(FString QuestIdent)
{
	return FQuestDetails();
}

FObjectiveDetails AQuest::GetObjectiveDetails(FString ObjectiveID)
{
	return FObjectiveDetails();
}

bool AQuest::IsObjectiveComplete(FString ObjectiveID)
{
	return false;
}

bool AQuest::AreAllObjectivesComplete()
{
	return false;
}

// Called every frame
void AQuest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
