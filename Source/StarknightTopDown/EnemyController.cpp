// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "EnemyAIState.h"
#include "Gameframework/Character.h"
#include "HealthComponent.h"
#include "HumanoidEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Hearing.h"
#include "PlayerCharacter.h"
#include "StatusEffectComponent.h"

AEnemyController::AEnemyController()
{
    BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
    check(BlackboardComp);

    BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));
    check(BehaviorTreeComp);
}

void AEnemyController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (InPawn == nullptr)return;

    if (!Player) Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	EnemyCharacter = Cast<ACharacter>(InPawn);
    if (EnemyCharacter)
    {
        auto HumanoidEnemy = Cast<AHumanoidEnemy>(EnemyCharacter);
        if (HumanoidEnemy)
        {
            UBehaviorTree* Behavior = HumanoidEnemy->GetBehaviorTree();
            if (Behavior)
            {
                BlackboardComp->InitializeBlackboard(*(Behavior->BlackboardAsset));

                BlackboardComp->SetValueAsObject(FName("SelfActor"), HumanoidEnemy);
                BlackboardComp->SetValueAsVector(FName("StartLocation"), HumanoidEnemy->GetActorLocation());
            }
        }
    }
}

void AEnemyController::UpdateBlackboard(UBlackboardComponent* InBlackboardComp)
{
    auto EnemyHealthComp = EnemyCharacter->GetComponentByClass<UHealthComponent>();
    auto HumanoidEnemy = Cast<AHumanoidEnemy>(EnemyCharacter);
    auto StatusComp = EnemyCharacter->GetComponentByClass<UStatusEffectComponent>();

    if(!Player) Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

    bPlayerVisible = LineOfSightTo(Player);

    if (bPlayerVisible)
    {
        InBlackboardComp->SetValueAsObject(FName("TargetActor"), Player);
        InBlackboardComp->SetValueAsVector(FName("TargetLocation"), Player->GetActorLocation());
        
        if(EnemyState != EEnemyAIState::EEAS_Combat) SetEnemyState(EEnemyAIState::EEAS_Combat);
    }
    else
    {
        InBlackboardComp->ClearValue(FName("TargetActor"));
        SetEnemyState(EEnemyAIState::EEAS_Alert);
    }

    InBlackboardComp->SetValueAsBool(FName("PlayerDead"), Player->GetPlayerIsDead());
    InBlackboardComp->SetValueAsBool(FName("SelfDead"), HumanoidEnemy->GetEnemyDead());

    if (EnemyHealthComp->CurrentHealth <= (EnemyHealthComp->MaxHealth / 2))
    {
        bBloodied = true;
    }
    else
    {
        bBloodied = false;
    }

    if (StatusComp)
    {
        if (StatusComp->QueryStatusEffects(EStatusEffect::ESE_Stunned))
        {
            bStunned = StatusComp->IsStatusActive(EStatusEffect::ESE_Stunned);
        }
    }

    InBlackboardComp->SetValueAsBool(FName("Bloodied"), bBloodied);
    InBlackboardComp->SetValueAsBool(FName("Stunned"), bStunned);

    uint8 StateByte = (uint8)EnemyState;
    InBlackboardComp->SetValueAsEnum(FName("State"),StateByte);
}
