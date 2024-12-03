// Fill out your copyright notice in the Description page of Project Settings.


#include "Destructable.h"
#include "HealthComponent.h"

// Sets default values
ADestructable::ADestructable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

// Called when the game starts or when spawned
void ADestructable::BeginPlay()
{
	Super::BeginPlay();
	
}

float ADestructable::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	HealthComp->TakeDamage(DamageAmount);

	HurtEffect();

	if (HealthComp->CurrentHealth <= 0.f)
	{
		HealthComp->bIsDead = true;
		//Destroy();
	}
	else
	{
		HealthComp->bIsDead = false;
	}
		
	return HealthComp->CurrentHealth;
	//UE_LOG(LogTemp, Warning, TEXT("Damage Taken"));
}

void ADestructable::HurtEffect_Implementation()
{
}

// Called every frame
void ADestructable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

