// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Collectable.h"
#include "PowerUp.generated.h"

/**
 * 
 */
UCLASS()
class SWOIMZ_API APowerUp : public ACollectable
{
	GENERATED_BODY()
	
	
		// the effect to generate
	UPROPERTY(EditAnywhere, Category = "Effect")
		TSubclassOf<class UEffect>  WhichEffect;

	UPROPERTY(EditAnywhere, Category = "Effect")
		UParticleSystem* WhichParticle;
	


	virtual void NotifyActorBeginOverlap(AActor* otherActor) override;
};
