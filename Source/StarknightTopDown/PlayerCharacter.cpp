// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "AmmoType.h"
#include "Camera/CameraComponent.h"
#include "Components/AudioComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "Engine/DamageEvents.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "HealthComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "WeaponsComponent.h"
#include "QuestLogComponent.h"
#include "InputAction.h"
#include "Core/InteractorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "StatusEffectComponent.h"
#include "Sound/SoundBase.h"
#include "TimerManager.h"
#include "Projectile.h"

APlayerCharacter::APlayerCharacter()
{
	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	//CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->SetRelativeRotation(FRotator(180.f,0.f,0.f));

	// Create a camera and attach to boom
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Comp"));
	CameraComp->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false; // We don't want the controller rotating the camera
	//CameraComp->SetProjectionMode(ECameraProjectionMode::Orthographic);
	//CameraComp->SetOrthoWidth(PlayerOrthoWidth);

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetupAttachment(GetMesh());

	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Comp"));
	WeaponComp = CreateDefaultSubobject<UWeaponsComponent>(TEXT("Weapon Comp"));
	StatusComp = CreateDefaultSubobject<UStatusEffectComponent>(TEXT("Status Comp"));
	QuestLog = CreateDefaultSubobject<UQuestLogComponent>(TEXT("Quest Log"));

	ChargingLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Charging Light"));
	ChargingLight->SetupAttachment(WeaponMesh, FName("Barrel"));
	ChargingLight->SetVisibility(false);

	InteractorComp = CreateDefaultSubobject<UInteractorComponent>(TEXT("Interactor Comp"));
}


void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	EquipPlasmaGun();
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(CombatMappingContext, 0);

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	Input->BindAction<APlayerCharacter>(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
	Input->BindAction<APlayerCharacter>(PrimaryInputAction, ETriggerEvent::Started, this, &APlayerCharacter::SetPrimaryDown);
	Input->BindAction<APlayerCharacter>(PrimaryInputAction, ETriggerEvent::Completed, this, &APlayerCharacter::SetPrimaryDown);
	Input->BindAction<APlayerCharacter>(SecondaryInputAction, ETriggerEvent::Started, this, &APlayerCharacter::SetSecondaryDown);
	Input->BindAction<APlayerCharacter>(SecondaryInputAction, ETriggerEvent::Completed, this, &APlayerCharacter::SetSecondaryDown);
	Input->BindAction<APlayerCharacter>(Hotkey1Action, ETriggerEvent::Triggered, this, &APlayerCharacter::EquipPlasmaGun);
	Input->BindAction<APlayerCharacter>(Hotkey2Action, ETriggerEvent::Triggered, this, &APlayerCharacter::EquipLightningGun);
	Input->BindAction<APlayerCharacter>(Hotkey3Action, ETriggerEvent::Triggered, this, &APlayerCharacter::EquipQuaker);
	//Input->BindAction<APlayerCharacter>(DashAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Dash);
	//Input->BindAction<APlayerCharacter>(PrimaryInputAction, ETriggerEvent::, this, &APlayerCharacter::SetPrimaryUp);
}

void APlayerCharacter::SetPrimaryDown(const FInputActionValue& KeyValue)
{
	bPrimaryDown = KeyValue.Get<bool>();
	
	if (bPrimaryDown)
	{
		PrimaryAction();

		if (ChargeEffect)ChargeEffect->DestroyComponent();
		if (ChargeSound)
		{
			ChargeSound->Stop();
			ChargeSound->DestroyComponent();
		}
		ChargingLight->SetVisibility(false);

		if(WeaponComp->EquippedWeapon.WeaponCharge)ChargeEffect = UNiagaraFunctionLibrary::SpawnSystemAttached(
			WeaponComp->EquippedWeapon.WeaponCharge,
			WeaponMesh,
			FName("Barrel"),
			WeaponMesh->GetSocketLocation(FName("Barrel")),
			WeaponMesh->GetSocketRotation(FName("Barrel")),
			EAttachLocation::KeepWorldPosition,
			false
		);
		if(WeaponComp->EquippedWeapon.WeaponChargeSound)ChargeSound = UGameplayStatics::SpawnSound2D(
			GetWorld(),
			WeaponComp->EquippedWeapon.WeaponChargeSound
		);

		if(ChargeSound)ChargeSound->Play(0.f);

		ChargingLight->SetVisibility(true);
	}
	else
	{
		if ((CurrentChargeAmount >= 1.0f)&&(WeaponComp->EquippedWeapon.ChargedProjectileClass)) SecondaryAction();
		
		ChargeEffect->DestroyComponent();
		ChargeSound->Stop();
		ChargeSound->DestroyComponent();
		ChargingLight->SetVisibility(false);
	}

	CurrentChargeAmount = 0.f;
}

void APlayerCharacter::SetSecondaryDown(const FInputActionValue& KeyValue)
{
	bSecondaryDown = KeyValue.Get<bool>();
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Look();

	if (bPrimaryDown)
	{
		CurrentChargeAmount += .01f;
	}
}

void APlayerCharacter::Move(const FInputActionValue& AxisValue)
{
	float MoveX = AxisValue.Get<FVector2D>().X;
	float MoveY = AxisValue.Get<FVector2D>().Y;
	FVector MovementVector (MoveY, MoveX, 0.f);

	AddMovementInput(MovementVector);
}

void APlayerCharacter::Look()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	FVector MouseWorldLocation;
	FVector MouseWorldRotation;
	FVector BeamEndLocation;

	FHitResult ScreenTraceHit;

	bool CursorToWorld = PlayerController->DeprojectMousePositionToWorld(MouseWorldLocation,MouseWorldRotation);
	
	FVector End{MouseWorldLocation + MouseWorldRotation * 2000};

	if (CursorToWorld)
	{
		GetWorld()->LineTraceSingleByChannel(ScreenTraceHit, MouseWorldLocation, End, ECollisionChannel::ECC_GameTraceChannel1);

		if (ScreenTraceHit.bBlockingHit)
		{
			BeamEndLocation = ScreenTraceHit.Location;
		}

		FRotator PlayerRotation = (BeamEndLocation - GetActorLocation()).Rotation();
		SetActorRotation(FRotator(0.f,PlayerRotation.Yaw,0.f));
	}
}

void APlayerCharacter::Interact()
{
}

void APlayerCharacter::Dash()
{
	FVector CurrentLocation = GetActorLocation();
	FVector TargetLocation = GetActorForwardVector() * 200;

	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, CurrentLocation+TargetLocation, GetWorld()->GetDeltaSeconds(), 60.f);
	SetActorLocation(NewLocation);
}

void APlayerCharacter::PrimaryAction()
{
	if (WeaponComp->GetCanBeFired() == false)return;
	//if (WeaponComp->HasAmmo(WeaponComp->EquippedWeapon.WeaponAmmoType) == false)return;

	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	FVector MouseWorldLocation;
	FVector MouseWorldRotation;
	FVector BeamEndLocation;

	FHitResult ScreenTraceHit;

	bool CursorToWorld = PlayerController->DeprojectMousePositionToWorld(MouseWorldLocation, MouseWorldRotation);

	FVector End{ MouseWorldLocation + MouseWorldRotation * 2000 };

	if (CursorToWorld)
	{
		GetWorld()->LineTraceSingleByChannel(ScreenTraceHit, MouseWorldLocation, End, ECollisionChannel::ECC_Visibility);

		if (ScreenTraceHit.bBlockingHit)
		{
			WeaponComp->FireEquippedWeapon(WeaponMesh, ScreenTraceHit.Location);
		}
	}
}

void APlayerCharacter::SecondaryAction()
{
	if (WeaponComp->GetCanBeFired() == false)return;
	if (WeaponComp->HasAmmo(WeaponComp->EquippedWeapon.WeaponAmmoType) == false)return;

	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	FVector MouseWorldLocation;
	FVector MouseWorldRotation;
	FVector BeamEndLocation;

	FHitResult ScreenTraceHit;

	bool CursorToWorld = PlayerController->DeprojectMousePositionToWorld(MouseWorldLocation, MouseWorldRotation);

	FVector End{ MouseWorldLocation + MouseWorldRotation * 2000 };

	if (CursorToWorld)
	{
		GetWorld()->LineTraceSingleByChannel(ScreenTraceHit, MouseWorldLocation, End, ECollisionChannel::ECC_Visibility);

		if (ScreenTraceHit.bBlockingHit)
		{
			WeaponComp->FireSecondary(WeaponMesh, ScreenTraceHit.Location);
		}
	}
}

void APlayerCharacter::EquipPlasmaGun()
{
	if(WeaponComp->QueryWeapons(EAmmoType::EAT_Plasma))
	{
		WeaponComp->EquipWeapon("PlasmaGun");
		WeaponMesh->SetStaticMesh(WeaponComp->EquippedWeapon.WeaponMesh);
		ChargingLight->SetLightColor(FLinearColor(1.f, .1f, 0.f, 1.f));
	}
}

void APlayerCharacter::EquipLightningGun()
{
	if (WeaponComp->QueryWeapons(EAmmoType::EAT_Voltaic))
	{
		WeaponComp->EquipWeapon("LightningGun");
		WeaponMesh->SetStaticMesh(WeaponComp->EquippedWeapon.WeaponMesh);
		ChargingLight->SetLightColor(FLinearColor(.2f, .2f, 1.f, 1.f));
	}
}

void APlayerCharacter::EquipQuaker()
{
	if (WeaponComp->QueryWeapons(EAmmoType::EAT_ThunderRound))
	{
		WeaponComp->EquipWeapon("Quaker");
		WeaponMesh->SetStaticMesh(WeaponComp->EquippedWeapon.WeaponMesh);
	}
}

void APlayerCharacter::ResetCanTakeDamage()
{
	bInvulnerable = false;
}

void APlayerCharacter::HurtEffect_Implementation()
{
}

void APlayerCharacter::OnDeath_Implementation()
{
}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (bInvulnerable == true)
	{
		return 0.f;
	}
	else
	{
		bInvulnerable = true;
		HealthComp->TakeDamage(DamageAmount);
		HurtEffect();

		GetWorld()->GetTimerManager().SetTimer(HurtHandle, this, &APlayerCharacter::ResetCanTakeDamage, HurtReactTime);

		LaunchCharacter(DamageCauser->GetActorForwardVector() * DamageKnockback, true, true);

		if (HealthComp->CurrentHealth <= 0.f)
		{
			HealthComp->bIsDead = true;
		}
		else
		{
			HealthComp->bIsDead = false;
			//trigger status effects here if the player is subject to those mechanics
		}

		return DamageAmount;
	}
}

