// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SwoimerAICollectorII.h"
#include "SwoimerAICollectorIII.generated.h"

/**
 * 
 */
UCLASS()
class SWOIMZ_API USwoimerAICollectorIII : public USwoimerAICollectorII
{
	GENERATED_BODY()
	
		virtual FVector GetSwoimerAcceleration(class ASwoim* swoimer) override;
	
	
};
