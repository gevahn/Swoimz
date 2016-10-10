// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseSwoimerAI.h"
#include "SwoimerAIMovementI.generated.h"

/**
 * 
 */
UCLASS()
class SWOIMZ_API USwoimerAIMovementI : public UBaseSwoimerAI
{
	GENERATED_BODY()

public:
	
	virtual FVector GetSwoimerAcceleration(class ASwoim* swoimer) override;
	
	FVector separate();
	FVector align();
	FVector cohesion();

	float SepFactor;
	float AliFactor;
	float CohFactor;

	float SepDistance;
	float AliDistance;
	float CohDistance;

	FVector velocity;
	FVector acceleration;

	FVector lastX;
	float lastDt;
	
};
