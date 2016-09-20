// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CollectableSpawner.generated.h"

UCLASS()
class SWOIMZ_API ACollectableSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectableSpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// reutrns the box to spawn
	FORCEINLINE UBoxComponent* GetWhereToSpawn() const { return WhereToSpawn; }

	// Find a random point
	UFUNCTION(BlueprintPure, Category = "Spwaning")
		FVector GetRandomPointInVolume();

	

protected:
	// the pickup to spawn
	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class ACollectable> WhatToSpawn;

private:
	//box componenet to spawn in
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateACcess = "true"))
		class UBoxComponent* WhereToSpawn;

	// Spawn a new swoimer
	ACollectable* SpawnCollectable();

	// Random Timer
	int time;
	
};
