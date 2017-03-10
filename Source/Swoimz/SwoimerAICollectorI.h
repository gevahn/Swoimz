// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseSwoimerAI.h"
#include "SwoimerAICollectorI.generated.h"

/**
 * 
 */
UCLASS()
class SWOIMZ_API USwoimerAICollectorI : public UBaseSwoimerAI
{
	GENERATED_BODY()
	
public:
	virtual FVector GetSwoimerAcceleration(class ASwoim* swoimer) override;
	virtual class AResource* GetResourceToCollect();
	AResource* targetToCollect = NULL;
	FVector acceleration;
	FVector targetLocation;

};
