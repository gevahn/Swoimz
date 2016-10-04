// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Hive.generated.h"

UCLASS()
class SWOIMZ_API AHive : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHive();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;


	//AHive* EnemyHive;
	// reutrns the box to spawn
	FORCEINLINE UBoxComponent* GetWhereToSpawn() const { return WhereToSpawn; }

	// Find a random point
	UFUNCTION(BlueprintPure, Category = "Spawning")
		FVector GetRandomPointInVolume();

	// Spawn a new swoimer
	UFUNCTION(BlueprintCallable, Category = "Spawning")
		void SpawnController(FVector center, int32 type);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		int32 CurrentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		int32 MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
		int32 Resource;

	virtual void NotifyActorBeginOverlap(AActor* otherActor) override;

	void DamageHive(AHive* hive, float damage);
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
