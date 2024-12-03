// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIState.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class STARKNIGHTTOPDOWN_API AEnemyController : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemyController();
	
	virtual void OnPossess(APawn* InPawn) override;

	void UpdateBlackboard(UBlackboardComponent* InBlackboardComp);

protected:

private:
	UPROPERTY(BlueprintReadWrite, Category = "AI Behavior", meta = (AllowPrivateAccess = true))
	class UBlackboardComponent* BlackboardComp;

	UPROPERTY(BlueprintReadWrite, Category = "AI Behavior", meta = (AllowPrivateAccess = true))
	class UBehaviorTreeComponent* BehaviorTreeComp;

	UPROPERTY(BlueprintReadWrite, Category = "AI Behavior", meta = (AllowPrivateAccess = true))
	class ACharacter* EnemyCharacter;

	UPROPERTY(BlueprintReadWrite, Category = "AI Behavior", meta = (AllowPrivateAccess = true))
	bool bPlayerVisible;
	
	UPROPERTY(BlueprintReadWrite, Category = "AI Behavior", meta = (AllowPrivateAccess = true))
	bool bBloodied;

	UPROPERTY(BlueprintReadWrite, Category = "AI Behavior", meta = (AllowPrivateAccess = true))
	bool bStunned;

	UPROPERTY(BlueprintReadWrite, Category = "AI Behavior", meta = (AllowPrivateAccess = true))
	class APlayerCharacter* Player;

	UPROPERTY(BlueprintReadWrite, Category = "AI Behavior", meta = (AllowPrivateAccess = true))
	EEnemyAIState EnemyState;

public:
	FORCEINLINE UBlackboardComponent* GetBlackboardComponent() const { return BlackboardComp; }

	FORCEINLINE EEnemyAIState GetEnemyState() const { return EnemyState; }

	void SetEnemyState(EEnemyAIState AIState) { EnemyState = AIState; }

	void SetStunned(bool bNewStunned) { bStunned = bNewStunned; }
};
