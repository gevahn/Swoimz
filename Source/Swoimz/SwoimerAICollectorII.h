// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SwoimerAICollectorI.h"
#include "SwoimerAICollectorII.generated.h"

/**
 * 
 */
UCLASS()
class SWOIMZ_API USwoimerAICollectorII : public USwoimerAICollectorI
{
	GENERATED_BODY()
public:
	class AResource* GetResourceToCollect() override;
	
	
};
