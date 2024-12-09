// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h" 
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Sound/SoundBase.h"
#include "StatusEffectComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	RootComponent = CollisionSphere;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh -> SetupAttachment(CollisionSphere);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Comp"));
	
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileOwner = GetOwner();

	//MovementComp->Deactivate();
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CollisionSphere -> IgnoreActorWhenMoving(ProjectileOwner, true);
	CollisionSphere->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//FTimerHandle DelayHandle;
	//GetWorld()->GetTimerManager().SetTimer(DelayHandle, this, &AProjectile::ActivateProjectile, 0.2f);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	if (ProjectileOwner == nullptr)
	{
		ProjectileOwner = GetOwner();
		//Destroy();
	}

	AController* MyOwnerInstigator = ProjectileOwner->GetInstigatorController();
	//UClass* DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != ProjectileOwner)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, ProjectileOwner, WeaponDamageType);
		
		auto StatusComp = OtherActor->GetComponentByClass<UStatusEffectComponent>();
		if (StatusComp)
		{
			if (StatusComp->QueryStatusEffects(ProjectileEffect) == true)
			{
				StatusComp->SetStatusEffect(ProjectileEffect, true);
			}
		}

		if (HitParticles)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
		}
		/*if (HitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		}*/
	}
	Destroy();
}

void AProjectile::ActivateProjectile()
{
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MovementComp->Activate();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

