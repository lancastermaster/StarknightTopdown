// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

float UHealthComponent::TakeDamage(float InDamage)
{
	InDamage = InDamage - DamageThreshold;

	if (InDamage > 0.f)
	{
		float OutHealth = CurrentHealth - InDamage;

		if (OutHealth <= 0.f) 
		{ 
			CurrentHealth = 0.f; 
			return 0.f;
			//if InDamage is large enough, the character should gib or send a gib message
			//Gibbing = true if InDamage >= CurrentHealth * 2 
		}
		else
		{
			CurrentHealth = OutHealth;
			if (OutHealth <= (MaxHealth / BloodiedMod)) bIsBloodied = true;
			else bIsBloodied = false;

			return OutHealth;
		}
	}
	else return CurrentHealth;
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

