// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestSystemInterface.h"
#include "QuestCallerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STARKNIGHTTOPDOWN_API UQuestCallerComponent : public UActorComponent, public IQuestSystemInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UQuestCallerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	class UQuestLogComponent* PlayerLog;

private:

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Quest")
	FString QuestToCall;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Quest System")
	void CallReceived();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Quest System")
	void CallSent();

	virtual void CallQuestID(FString QuestID) override;

	virtual void ReceiveQuestID(FString QuestID) override;
};
