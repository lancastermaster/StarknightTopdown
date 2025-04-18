// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "QuestCallerComponent.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Frame"));

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	DoorMesh->SetupAttachment(DoorFrame);

	QuestCaller = CreateDefaultSubobject<UQuestCallerComponent>(TEXT("Quest Caller"));
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADoor::CheckLocks()
{
	int LocksNumber = 0;

	if (Locks.IsEmpty()) OpenDoor();
	else
	{
		for (auto lock : Locks)
		{
			if(lock.Value == true)LocksNumber++;
		}

		if (LocksNumber >= Locks.Num())
		{
			SetDoorOpen(true);
			OpenDoor();
		}
		else
		{ 
			SetDoorOpen(false);
			OpenDoor();
		}
	}
}

void ADoor::CallReceived_Implementation()
{
}

void ADoor::CallSent_Implementation()
{
}

void ADoor::OpenDoor_Implementation()
{
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

