// Fill out your copyright notice in the Description page of Project Settings.

#include "Swoimz.h"
#include "Hive.h"
#include "Swoim.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"
#include "SwoimController.h"

// Sets default values
AHive::AHive()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// create the box for spawn volume
	WhereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
	RootComponent = WhereToSpawn;
}

// Called when the game starts or when spawned
void AHive::BeginPlay()
{
	Super::BeginPlay();
	
	time = 0;
}

// Called every frame
void AHive::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if (time <= 0)
	{
		
		time = (int)FMath::FRandRange(100, 300);
	}
	else
	{
		time -= DeltaTime;
	}
}

// Gets a random point inside the volume
FVector AHive::GetRandomPointInVolume()
{
	FVector SpawnOrigin = WhereToSpawn->Bounds.Origin;
	FVector SpawnExtent = SpawnOrigin + WhereToSpawn->Bounds.BoxExtent;

	
	return FVector(FMath::FRandRange(SpawnOrigin.X, SpawnExtent.X), FMath::FRandRange(SpawnOrigin.Y, SpawnExtent.Y), FMath::FRandRange(SpawnOrigin.Z, SpawnExtent.Z));

}

// Spawns a collectable 
void AHive::SpawnController(FVector center)
{
	UE_LOG(LogTemp, Warning, TEXT("spawn swoim called"));

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
			UE_LOG(LogTemp, Warning, TEXT("center: %s"), *center.ToString());
			FRotator SpawnRotation;
			SpawnRotation.Yaw = FMath::FRand() * 360.0f;
			SpawnRotation.Pitch = FMath::FRand() * 360.0f;
			SpawnRotation.Roll = FMath::FRand() * 360.0f;
			ASwoimController* spawnedSwoimer = World->SpawnActor<ASwoimController>(WhatToSpawn, SpawnLocation, SpawnRotation, SpawnParams);
			spawnedSwoimer->center = center;
			UE_LOG(LogTemp, Warning, TEXT("after spawn center: %s"), *spawnedSwoimer->center.ToString());
			SwoimersArray.Add(spawnedSwoimer);

		}
	}
}