// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestLogComponent.h"
#include "QuestSystemData.h"
#include "Engine/DataTable.h"
#include "Engine/EngineTypes.h"
#include "Kismet/GameplayStatics.h"
#include "QuestSystemInterface.h"

// Sets default values for this component's properties
UQuestLogComponent::UQuestLogComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UQuestLogComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	InitializeQuestData();
}

void UQuestLogComponent::CompleteQuest(FString QuestID)
{
	if (QuestProgress.QuestProgress[QuestID] >= QuestData[QuestID].Quantity)
	{
		//QuestProgress.IsComplete[QuestID] = true;
		QuestProgress.IsComplete.Add(QuestID, true);
	}
}

void UQuestLogComponent::ProgressQuest(FString QuestID)
{
	int ProgressToIncrease = QuestProgress.QuestProgress[QuestID];
	ProgressToIncrease++;
	QuestProgress.QuestProgress.Add(QuestID,ProgressToIncrease);
	
	CompleteQuest(QuestID); //Will do nothing if progress doesn't meet the correct threshold

	CallQuestID(QuestID);
}

void UQuestLogComponent::InitializeQuestData()
{
	TArray<FName> RowNames = QuestDataTable->GetRowNames();

	for (FName row : RowNames)
	{
		FString RowID = row.ToString();
		FQuestDetails* RowInfo = QuestDataTable->FindRow<FQuestDetails>(row, FString(""));
		FQuestDetails ValueToAdd;

		if (RowInfo)
		{
			ValueToAdd.Name = RowInfo->Name;
			ValueToAdd.Description = RowInfo->Description;
			ValueToAdd.Type = RowInfo->Type;
			ValueToAdd.Quantity = RowInfo->Quantity;
		}
		QuestData.Add(RowID, ValueToAdd);

		QuestProgress.QuestProgress.Add(row.ToString(), 0);
	}


}

// Called every frame
void UQuestLogComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

/*void UQuestLogComponent::CallQuestID(FString QuestID)
{
	if (QuestData.Find(QuestID))
	{
		ProgressQuest(QuestID);
	}
}*/

void UQuestLogComponent::ReceiveQuestID(FString QuestID)
{
	if (QuestData.Find(QuestID))
	{
		ProgressQuest(QuestID);
	}
}

void UQuestLogComponent::CallQuestID(FString QuestID)
{
	TArray<AActor*> QuestComps; 
	UGameplayStatics::GetAllActorsWithInterface(this, UQuestSystemInterface::StaticClass(), QuestComps);

	for (AActor* actor : QuestComps)
	{
		if (actor==this->GetOwner()){} //only the player will have a Quest Log Component
		else
		{
			Cast<IQuestSystemInterface>(actor)->ReceiveQuestID(QuestID);
		}
	}
}