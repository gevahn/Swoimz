// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SwoimController.h"
#include "Swoim.generated.h"



UCLASS()
class SWOIMZ_API ASwoim : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASwoim();

	FVector velocity;
	FVector acceleration;
	FVector avoidAhead;

	FVector center;
	float mass;

	float maxspeed;


	float Speedlimit;

	float Forcelimit;

	
	TWeakObjectPtr<ASwoimController> SwoimController;

	float SepDistance;
	float AliDistance;
	float CohDistance;

	UPROPERTY(EditAnywhere)
		float SepFactor;
	UPROPERTY(EditAnywhere)
		float AliFactor;
	UPROPERTY(EditAnywhere)
		float CohFactor;
	UPROPERTY(EditAnywhere)
		float CenFactor;
	UPROPERTY(EditAnywhere)
		float LookAheadDistance;
	float LookAheadDecay;
	float AvoFactor1;
	float AvoFactor2;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	TArray<ASwoim*> SwoimersArray;

	UFUNCTION()
		void OnUpCohPressed();
	UFUNCTION()
		void OnDownCohPressed();
	// Return the mesh for the swarmer
	FORCEINLINE class UStaticMeshComponent* GetMesh() const { return SwarmerMesh; }

	bool TraceAhead(const FVector& Start, const FVector& End, UWorld* World, FHitResult& HitOut);

	FVector separate();

	FVector align();
	FVector cohesion();
	FVector seek(FVector target);
	FVector avoid(FHitResult& HitData);


private:
	// pasic swarmer
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Swarmer", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* SwarmerMesh;

};
