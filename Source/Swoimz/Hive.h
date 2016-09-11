// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Hive.generated.h"

UCLASS()
class SWOIMZ_API AHive : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHive();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// reutrns the box to spawn
	FORCEINLINE UBoxComponent* GetWhereToSpawn() const { return WhereToSpawn; }

	// Find a random point
	UFUNCTION(BlueprintPure, Category = "Spawning")
		FVector GetRandomPointInVolume();

	// Spawn a new swoimer
	UFUNCTION(BlueprintCallable, Category = "Spawning")
		void SpawnController(FVector center);
	/*
	// Which effect to spawn
	UPROPERTY(EditAnywhere, Category = "Effect")
		TSubclassOf<class UEffect>  WhichEffect;

	UPROPERTY(EditAnywhere, Category = "Effect")
		UParticleSystem* WhichParticle;
	*/
protected:
	// the pickup to spawn
	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class ASwoimController> WhatToSpawn;
	

private:
	//box componenet to spawn in
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateACcess = "true"))
		class UBoxComponent* WhereToSpawn;

	TArray<class ASwoimController*> SwoimersArray;



	// Random Timer
	int time;
};
