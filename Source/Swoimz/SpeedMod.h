// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Effect.h"
#include "SpeedMod.generated.h"

/**
 * 
 */
UCLASS()
class SWOIMZ_API USpeedMod : public UEffect
{
	GENERATED_BODY()

	USpeedMod();
	virtual void BeginPlay() override;

<<<<<<< HEAD
=======
	float speedChange = 50;
	
>>>>>>> origin/master
	virtual void ApplyEffect(float DeltaTime) override;
	virtual void RemoveEffect() override;
	
};
