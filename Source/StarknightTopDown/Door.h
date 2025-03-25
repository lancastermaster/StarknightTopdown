// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestSystemInterface.h"
#include "Door.generated.h"

UCLASS()
class STARKNIGHTTOPDOWN_API ADoor : public AActor, public IQuestSystemInterface 
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* DoorFrame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UQuestCallerComponent* QuestCaller;
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bDoorOpen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UDamageTypeBase> DamageFilter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<AActor*, bool> Locks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float OpenTime;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void TriggerLock(AActor* LockActor, bool LockState) { Locks.Add(LockActor, LockState); }

	UFUNCTION(BlueprintCallable)
	void SetDoorOpen(bool DoorOpen) { bDoorOpen = DoorOpen; }

	UFUNCTION(BlueprintCallable)
	void CheckLocks();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OpenDoor();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Quest System")
	void CallReceived();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Quest System")
	void CallSent();
};
