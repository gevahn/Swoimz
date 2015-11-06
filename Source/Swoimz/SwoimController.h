// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "SwoimController.generated.h"

UCLASS()
class SWOIMZ_API ASwoimController : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASwoimController();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	// reutrns the box to spawn
	FORCEINLINE UBoxComponent* GetWhereToSpawn() const { return WhereToSpawn; }

	// Find a random point
	UFUNCTION(BlueprintPure, Category = "Spwaning")
		FVector GetRandomPointInVolume();

	UPROPERTY(EditAnywhere)
		float Speedlimit;

	UPROPERTY(EditAnywhere)
		float Forcelimit;

	UPROPERTY(EditAnywhere)
		float SepFactor;
	UPROPERTY(EditAnywhere)
		float AliFactor;
	UPROPERTY(EditAnywhere)
		float CohFactor;
	UPROPERTY(EditAnywhere)
		float CenFactor;
	UPROPERTY(EditAnywhere)
		float AvoFactor1;
	UPROPERTY(EditAnywhere)
		float AvoFactor2;
	UPROPERTY(EditAnywhere)
		float SepDistance;
	UPROPERTY(EditAnywhere)
		float AliDistance;
	UPROPERTY(EditAnywhere)
		float CohDistance;
	UPROPERTY(EditAnywhere)
		float LookAheadDistance;
	UPROPERTY(EditAnywhere)
		float LookAheadDecay;

protected:
	// the pickup to spawn
	UPROPERTY(EditAnywhere, Category = "Spawing")
		TSubclassOf<class ASwoim> WhatToSpawn;

private:
	//box componenet to spawn in
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawing", meta = (AllowPrivateACcess = "true"))
	class UBoxComponent* WhereToSpawn;

	// Spawn a new pickup
	ASwoim* SpawnSwoimer();

	
	
};
