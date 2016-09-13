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

	FVector lastX;
	float lastDt;

	FVector avoidAhead;

	FVector center;
	float mass;

	float maxspeed;

	int32 CurrentHealth;
	int32 MaxHealth;


	float Speedlimit;

	float Forcelimit;

	
	TWeakObjectPtr<class ASwoimController> SwoimController;
	ASwoim* targetSwoimer;

	float SepDistance;
	float AliDistance;
	float CohDistance;

	bool debugSwoimer = false;

	UPROPERTY(EditAnywhere)
		float SepFactor;
	UPROPERTY(EditAnywhere)
		float AliFactor;
	UPROPERTY(EditAnywhere)
		float CohFactor;
	UPROPERTY(EditAnywhere)
		float CenFactor;
	UPROPERTY(EditAnywhere)
		float AtkFactor;
	UPROPERTY(EditAnywhere)
		float LookAheadDistance;
	float LookAheadDecay;
	float AvoFactor1;
	float AvoFactor2;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual void NotifyActorBeginOverlap(AActor* otherActor) override;

	void DamageSwoimer(ASwoim* swoimer, float damage);

	UFUNCTION(BlueprintNativeEvent)
	void SparkOnOverlap();

	virtual void SparkOnOverlap_Implementation();


	TArray<ASwoim*> SwoimersArray;

	TArray<class UEffect* > ActiveEffects;

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

	FVector attack(ASwoim* targetSwoimer);


private:
	// basic swarmer
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Swarmer", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* SwarmerMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Swarmer", meta = (AllowPrivateAccess = "true"))
	class UMaterialBillboardComponent* HealthBar;

	
};
