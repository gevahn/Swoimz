// Fill out your copyright notice in the Description page of Project Settings.

#include "Swoimz.h"
#include "SpawnVolume.h"
#include "Kismet/KismetMathLibrary.h"
#include "Swoim.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)

// Sets default values
ASpawnVolume::ASpawnVolume()
{


	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// create the box for spawn volume
	WhereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
	RootComponent = WhereToSpawn;

}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	TArray<ASwoim*> SwoimersArray;
	for (int i = 0; i < 100; i++){
		SwoimersArray.Add(SpawnSwoimer());
	}
	print("swoimers spawned");
	for (int i = 0; i < 100; i++){
		SwoimersArray[i]->SwoimersArray = SwoimersArray;
		SwoimersArray[i]->center = WhereToSpawn->Bounds.Origin;
		SwoimersArray[i]->Speedlimit = Speedlimit;
		SwoimersArray[i]->Forcelimit = Forcelimit;
		SwoimersArray[i]->SepFactor = SepFactor;
		SwoimersArray[i]->AliFactor = AliFactor;
		SwoimersArray[i]->CohFactor = CohFactor;
		SwoimersArray[i]->CenFactor = CenFactor;
		SwoimersArray[i]->SepDistance = SepDistance;
		SwoimersArray[i]->AliDistance = AliDistance;
		SwoimersArray[i]->CohDistance = CohDistance;

	}
	UE_LOG(LogTemp, Warning, TEXT("swoimers updated"));

}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASpawnVolume::GetRandomPointInVolume()
{
	FVector SpawnOrigin = WhereToSpawn->Bounds.Origin;
	FVector SpawnExtent = WhereToSpawn->Bounds.BoxExtent;

	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);

}

ASwoim* ASpawnVolume::SpawnSwoimer()
{
	if (WhatToSpawn != NULL)
	{
		UWorld* const World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			FVector SpawnLocation = GetRandomPointInVolume();

			FRotator SpawnRotation;
			SpawnRotation.Yaw = FMath::FRand() * 360.0f;
			SpawnRotation.Pitch = FMath::FRand() * 360.0f;
			SpawnRotation.Roll = FMath::FRand() * 360.0f;

			return World->SpawnActor<ASwoim>(WhatToSpawn, SpawnLocation, SpawnRotation, SpawnParams);
		}
	}
	return NULL;
}


