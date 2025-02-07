// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanoidEnemy.h"
#include "HealthComponent.h"
#include "EnemyController.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/DamageType.h"
#include "StatusEffectComponent.h"
#include "DamageTypeBase.h"
#include "DamageTypeElectric.h"
#include "QuestCallerComponent.h"

AHumanoidEnemy::AHumanoidEnemy()
{
	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Comp"));

	StatusComp = CreateDefaultSubobject<UStatusEffectComponent>(TEXT("Status Comp"));

	QuestCaller = CreateDefaultSubobject<UQuestCallerComponent>(TEXT("Quest Caller"));
}

void AHumanoidEnemy::BeginPlay()
{
	Super::BeginPlay();

	Brain = Cast<AEnemyController>(GetController());
	if (Brain)
	{
		Brain->UpdateBlackboard(Brain->GetBlackboardComponent());
		Brain->RunBehaviorTree(BehaviorTree);
	}
}

void AHumanoidEnemy::Tick(float DeltaTime)
{
	if (Brain)
	{
		Brain->UpdateBlackboard(Brain->GetBlackboardComponent());
	}
}

float AHumanoidEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	TSubclassOf<UDamageType> InDamageType = DamageEvent.DamageTypeClass;
	HealthComp->TakeDamage(DamageAmount);

	HurtEffect();

	if (InDamageType == UDamageTypeElectric::StaticClass())//check for damage type this way
	{
		StatusComp->IncreaseStatusValue(DamageAmount, EStatusEffect::ESE_Stunned);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Damage Type not casting!"));
	}

	if (HealthComp->CurrentHealth <= 0.f)
	{
		HealthComp->bIsDead = true;
		Brain->SetEnemyState(EEnemyAIState::EEAS_Dead);
		Destroy();
	}
	else
	{
		HealthComp->bIsDead = false;
		Brain->SetEnemyState(EEnemyAIState::EEAS_Combat);

	}
	
	//ElectricDamage = Cast<UDamageTypeElectric>(DamageEvent.DamageTypeClass);


	//UE_LOG(LogTemp, Warning, TEXT("Damage Type = %s"), InDamageType->GetDisplayNameText());

	return 0.0f;
}

void AHumanoidEnemy::Attack_Implementation()
{
}

void AHumanoidEnemy::HurtEffect_Implementation()
{
}
