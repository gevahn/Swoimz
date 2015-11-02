// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
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

	FVector center;
	float mass;

	float maxspeed;


	float Speedlimit;

	float Forcelimit;

	


	float SepDistance;
	float AliDistance;
	float CohDistance;

	UPROPERTY(EditAnywhere)
		int32 SepFactor;
	UPROPERTY(EditAnywhere)
		int32 AliFactor;
	UPROPERTY(EditAnywhere)
		int32 CohFactor;
	UPROPERTY(EditAnywhere)
		int32 CenFactor;

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



	FVector separate();

	FVector align();
	FVector cohesion();
	FVector seek(FVector target);


private:
	// pasic swarmer
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Swarmer", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* SwarmerMesh;

};
