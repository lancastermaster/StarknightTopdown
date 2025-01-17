// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestSystemData.h"
#include "QuestSystemInterface.h"
#include "QuestLogComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STARKNIGHTTOPDOWN_API UQuestLogComponent : public UActorComponent, public IQuestSystemInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UQuestLogComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void CompleteQuest(FString QuestID);

	void ProgressQuest(FString QuestID);

	void InitializeQuestData();

	//LoadQuestProgress
	//SaveQuestProgress

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest Info", meta = (AllowPrivateAccess = "true"))
	UDataTable* QuestDataTable;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void CallQuestID(FString QuestID) override;

	virtual void ReceiveQuestID(FString QuestID) override;

	//void CallQuestID(FString QuestID);
	//TArray<class AQuest*> Quests; //becoming obsolete

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, FQuestDetails> QuestData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FQuestSaveData QuestProgress;
};
