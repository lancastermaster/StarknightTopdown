// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorLock.h"
#include "Door.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/DamageType.h"
#include "DamageTypeBase.h"

// Sets default values
ADoorLock::ADoorLock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lock Mesh"));
}

// Called when the game starts or when spawned
void ADoorLock::BeginPlay()
{
	Super::BeginPlay();
	
}

float ADoorLock::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!DamageFilter) SetLockState();
	else
	{
		if (DamageEvent.DamageTypeClass == DamageFilter)
		{
			SetLockState();
		}
	}

	return 0.0f;
}

void ADoorLock::SetLockState()
{
	bLocked = !bLocked;
	LockedDoor->TriggerLock(this, bLocked);
	LockedDoor->CheckLocks();

	if (!bLocked && LockTime>0.f) SetLockTimer();
}

void ADoorLock::SetLockTimer()
{
	FTimerHandle LockHandle;

	GetWorld()->GetTimerManager().SetTimer(LockHandle, this, &ADoorLock::SetLockState, LockTime);
}

// Called every frame
void ADoorLock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

