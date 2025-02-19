// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusEffectComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/DamageType.h"
#include "DamageTypeBase.h"
#include "DamageTypeElectric.h"
#include "DamageTypeThermal.h"
#include "StatusEffect.h"
#include "EnemyController.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

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
	
	if (!ActiveStunEffect)
	{
		if (StunnedEffect)
		{
			ActiveStunEffect = UNiagaraFunctionLibrary::SpawnSystemAttached(StunnedEffect, GetOwner()->GetComponentByClass<USkeletalMeshComponent>(), FName("Torso"), FVector(0.f), FRotator(0.f), EAttachLocation::SnapToTarget, false);
			ActiveStunEffect->Deactivate();
		}
	}
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

				if(ActiveStunEffect)ActiveStunEffect->Activate();

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
		ActiveStunEffect->Deactivate();

		UE_LOG(LogTemp, Warning, TEXT("Stunned Reset"));
	}
}

void UStatusEffectComponent::IncreaseStun(float Increase)
{
	StunValue += Increase;
	if (StunValue >= StatusEffectMax[EStatusEffect::ESE_Stunned])
	{
		if (!IsStatusActive(EStatusEffect::ESE_Stunned))
		{
			SetStatusEffect(EStatusEffect::ESE_Stunned, true);
		}
		StunValue = 0.f;
	}
}

void UStatusEffectComponent::IncreaseBurn(float Increase)
{
	BurnValue += Increase;
	if (BurnValue >= StatusEffectMax[EStatusEffect::ESE_Burnt])
	{
		if (!IsStatusActive(EStatusEffect::ESE_Burnt))
		{
			SetStatusEffect(EStatusEffect::ESE_Burnt, true);
		}
		BurnValue = 0.f;
	}
}

void UStatusEffectComponent::IncreaseStatusValue(float InDamage, EStatusEffect InStatusEffect)
{
	if (InDamage > 0.f)
	{
		switch (InStatusEffect)
		{
			case EStatusEffect::ESE_Stunned:
				StunValue += InDamage;
				if (StunValue >= StatusEffectMax[EStatusEffect::ESE_Stunned])
				{
					if (!IsStatusActive(EStatusEffect::ESE_Stunned))
					{
						SetStatusEffect(EStatusEffect::ESE_Stunned, true);
					}
					StunValue = 0.f;
				}
				break;

			case EStatusEffect::ESE_Burnt:
				BurnValue += InDamage;
				if (BurnValue >= StatusEffectMax[EStatusEffect::ESE_Burnt])
				{
					if (!IsStatusActive(EStatusEffect::ESE_Burnt))
					{
						SetStatusEffect(EStatusEffect::ESE_Burnt, true);
					}
					BurnValue = 0.f;
				}
				break;
		}
	}
}



