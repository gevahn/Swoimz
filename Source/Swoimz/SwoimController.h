// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Pawn.h"
#include "SwoimController.generated.h"

UCLASS()
class SWOIMZ_API ASwoimController : public APawn
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	// Sets default values for this pawn's properties
	ASwoimController();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	FVector center;

	TArray<class ASwoim*> SwoimersArray;

	// reutrns the box to spawn
	FORCEINLINE UBoxComponent* GetWhereToSpawn() const { return WhereToSpawn; }
	
	// Find a random point
	UFUNCTION(BlueprintPure, Category = "Spwaning")
		FVector GetRandomPointInVolume();
		
	UPROPERTY(EditAnywhere)
		float Speedlimit;

	UPROPERTY(EditAnywhere)
		float Forcelimit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SepFactor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AliFactor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CohFactor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CenFactor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AvoFactor1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AvoFactor2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SepDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AliDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CohDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AtkFactor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LookAheadDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LookAheadDecay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool CameraOptionSwitch;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float attackRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 NumberOfSwoimers;

	void AttackSwoim();

	void Disengage();

	void Disperse();

	void ReturnToFlock();

	void ZoomCamera(float AxisValue);
	void CameraCenter();

	void IncreaseCohFactor();
	void DecreaseCohFactor();

	void IncreaseSepFactor();
	void DecreaseSepFactor();

	void IncreaseAliFactor();
	void DecreaseAliFactor();

	void IncreaseCohDistance();
	void DecreaseCohDistance();

	void IncreaseSepDistance();
	void DecreaseSepDistance();

	void IncreaseAliDistance();
	void DecreaseAliDistance();
	

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
