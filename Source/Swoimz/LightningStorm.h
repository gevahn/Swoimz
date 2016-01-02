// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Hazard.h"
#include "LightningStorm.generated.h"

/**
 * 
 */
UCLASS()
class SWOIMZ_API ALightningStorm : public AHazard
{
	GENERATED_BODY()

public:
	ALightningStorm();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UParticleSystemComponent * Fire(class ASwoim* first, class ASwoim* second);

	UPROPERTY(EditAnywhere)
	float Damage;

	UPROPERTY(EditAnywhere)
	float ArcDistance;

	UPROPERTY(EditAnywhere)
		float NumOfLights;

	TArray<UParticleSystemComponent *> LightiningsArray;

private:
	//box componenet to spawn in
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Box", meta = (AllowPrivateACcess = "true"))
	class UBoxComponent* StormBox;

	UPROPERTY(EditAnywhere, Category = "Effect")
	UParticleSystem* LightiningParticle;

	
	
	
	
};
