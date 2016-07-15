// Fill out your copyright notice in the Description page of Project Settings.

#include "Swoimz.h"
#include "CollectableSpawner.h"
#include "Swoim.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"
#include "Collectable.h"
#include "Effect.h"

// Sets default values
ACollectableSpawner::ACollectableSpawner()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// create the box for spawn volume
	WhereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
	RootComponent = WhereToSpawn;

}

// Called when the game starts or when spawned
void ACollectableSpawner::BeginPlay()
{
	Super::BeginPlay();
	time = 0;
}

// Called every frame
void ACollectableSpawner::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	//UE_LOG(LogTemp, Warning, TEXT("time %f"), time);
	if (time < 0)
	{
		time = 1;
		//UE_LOG(LogTemp, Warning, TEXT("time %f"),time);
		AActor* spawnedCollectable = SpawnCollectable();
		//time = (int)FMath::FRandRange(100, 300);
		//UE_LOG(LogTemp, Warning, TEXT("spawned collectable"));
		if (spawnedCollectable) {
			UE_LOG(LogTemp, Warning, TEXT("spawned collectable"));
			//spawnedCollectable->WhichEffect = WhichEffect;
//			spawnedCollectable->WhichParticle = WhichParticle;
		}
	}
	else
	{
		time -= DeltaTime;
	}
}

// Gets a random point inside the volume
FVector ACollectableSpawner::GetRandomPointInVolume()
{
	FVector SpawnOrigin = WhereToSpawn->Bounds.Origin;
	FVector SpawnExtent = SpawnOrigin + WhereToSpawn->Bounds.BoxExtent;


	return FVector(FMath::FRandRange(SpawnOrigin.X, SpawnExtent.X), FMath::FRandRange(SpawnOrigin.Y, SpawnExtent.Y), FMath::FRandRange(SpawnOrigin.Z, SpawnExtent.Z));

}

// Spawns a collectable 
AActor* ACollectableSpawner::SpawnCollectable()
{
	UE_LOG(LogTemp, Warning, TEXT("spawned collectable called"));
	if (WhatToSpawn != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("there is somwthing to spawn"));
		UWorld* const World = GetWorld();
		if (World)
		{
			UE_LOG(LogTemp, Warning, TEXT("there is a world"));
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			FVector SpawnLocation = GetRandomPointInVolume();
			UE_LOG(LogTemp, Warning, TEXT("loc %s"),*SpawnLocation.ToString());

			FRotator SpawnRotation;
			SpawnRotation.Yaw = FMath::FRand() * 360.0f;
			SpawnRotation.Pitch = FMath::FRand() * 360.0f;
			SpawnRotation.Roll = FMath::FRand() * 360.0f;

			return World->SpawnActor<AActor>(WhatToSpawn, SpawnLocation, SpawnRotation, SpawnParams);
		}
	}
	return NULL;
}