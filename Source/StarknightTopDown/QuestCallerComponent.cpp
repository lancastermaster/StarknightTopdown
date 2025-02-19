// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestCallerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"
#include "QuestLogComponent.h"
#include "HumanoidEnemy.h"
//#include "QuestSystemInterface.h"

// Sets default values for this component's properties
UQuestCallerComponent::UQuestCallerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UQuestCallerComponent::BeginPlay()
{
	Super::BeginPlay();

	auto Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	PlayerLog = Player->GetComponentByClass<UQuestLogComponent>();
}


// Called every frame
void UQuestCallerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UQuestCallerComponent::CallReceived_Implementation()
{
}

/*void UQuestCallerComponent::CallQuestID()
{
	if (PlayerLog) PlayerLog->CallQuestID(QuestToCall);
}*/

void UQuestCallerComponent::ReceiveQuestID(FString QuestID)
{
	if(QuestID==QuestToCall) CallReceived();
}

void UQuestCallerComponent::CallSent_Implementation()
{
	AActor* Owner = GetOwner();

	//if (Cast<AHumanoidEnemy>(Owner))
	//{
		CallQuestID(QuestToCall);
	//}
}

void UQuestCallerComponent::CallQuestID(FString QuestID)
{
	if (PlayerLog) PlayerLog->ReceiveQuestID(QuestID);
}

