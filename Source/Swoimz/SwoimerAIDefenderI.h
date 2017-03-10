// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseSwoimerAI.h"
#include "SwoimerAIDefenderI.generated.h"

/**
 * 
 */
UCLASS()
class SWOIMZ_API USwoimerAIDefenderI : public UBaseSwoimerAI
{
	GENERATED_BODY()
	
public:
	virtual FVector GetSwoimerAcceleration(class ASwoim* swoimer) override;
	ASwoim* targetSwoimer;

};
