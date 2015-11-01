#pragma once


#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"


UCLASS()
class SWOIMZ_API ASpawnVolume : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawnVolume();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

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
		int32 SepFactor;
	UPROPERTY(EditAnywhere)
		int32 AliFactor;
	UPROPERTY(EditAnywhere)
		int32 CohFactor;
	UPROPERTY(EditAnywhere)
		int32 CenFactor;
	UPROPERTY(EditAnywhere)
		float SepDistance;
	UPROPERTY(EditAnywhere)
		float AliDistance;
	UPROPERTY(EditAnywhere)
		float CohDistance;

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
