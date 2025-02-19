// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestReceiver.h"
#include "QuestSystemInterface.h"

// Sets default values
AQuestReceiver::AQuestReceiver()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AQuestReceiver::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AQuestReceiver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AQuestReceiver::ReceiveQuestID(FString QuestID)
{
	if (Quests.Contains(QuestID)) CallReceived();
}

void AQuestReceiver::CallReceived_Implementation()
{
}

