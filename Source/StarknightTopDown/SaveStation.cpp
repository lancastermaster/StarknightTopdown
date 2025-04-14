// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveStation.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "StarknightSaveGame.h"
#include "MainGameInstance.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASaveStation::ASaveStation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SaveStationMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Save Station Mesh"));
	SaveStationMesh->SetupAttachment(RootComponent);

	PlayerSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Player Spawn Point"));
	PlayerSpawnPoint->SetupAttachment(SaveStationMesh);

	SaveStationCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Save Station Collision"));
	SaveStationCollision->SetupAttachment(SaveStationMesh);
}

// Called when the game starts or when spawned
void ASaveStation::BeginPlay()
{
	Super::BeginPlay();

	MainGameInstance = Cast<UMainGameInstance>(GetGameInstance());

	PlayerSaveGame = Cast<UStarknightSaveGame>(MainGameInstance->GetSaveGame());
	
	//SaveStationCollision->OnComponentBeginOverlap.AddDynamic(this, &ASaveStation::SaveGame);
}

// Called every frame
void ASaveStation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASaveStation::SaveGame()
{
	MainGameInstance->SaveLocation = PlayerSpawnPoint->GetComponentLocation();
}

