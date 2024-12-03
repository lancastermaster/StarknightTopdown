// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusEffectComponent.h"
#include "GameFramework/DamageType.h"
#include "StatusEffect.h"
#include "EnemyController.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UStatusEffectComponent::UStatusEffectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStatusEffectComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	
}


// Called every frame
void UStatusEffectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStatusEffectComponent::SetStatusEffect(EStatusEffect NewStatus, bool IsActive)
{
	FTimerHandle StunHandle;
	FTimerHandle BurnHandle;
	FTimerHandle SlowHandle;

	//StatusEffects.Add(NewStatus, IsActive);
	if (IsActive)
	{
		switch (NewStatus)
		{
			case EStatusEffect::ESE_Burnt:
			break;

			case EStatusEffect::ESE_Stunned:
				UE_LOG(LogTemp, Warning, TEXT("Stunned"));
				StatusEffects.Add(EStatusEffect::ESE_Stunned, true);

				if (GetWorld()->GetTimerManager().IsTimerActive(StunHandle) == false)
				{
					GetWorld()->GetTimerManager().SetTimer(StunHandle, this, &UStatusEffectComponent::ResetStunned, 3.f, false);
				}
			break;

			case EStatusEffect::ESE_Slowed:
			break;
		}
	}
}

bool UStatusEffectComponent::QueryStatusEffects(EStatusEffect Query)
{
	if (StatusEffects.Contains(Query))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool UStatusEffectComponent::IsStatusActive(EStatusEffect Query)
{
	bool bKeyPresent = QueryStatusEffects(Query);

	if (bKeyPresent)
	{
		if (StatusEffects[Query] == true)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

void UStatusEffectComponent::ResetStunned()
{
	if (IsStatusActive(EStatusEffect::ESE_Stunned))
	{
		StatusEffects.Add(EStatusEffect::ESE_Stunned, false);
		UE_LOG(LogTemp, Warning, TEXT("Stunned Reset"));
	}
}



