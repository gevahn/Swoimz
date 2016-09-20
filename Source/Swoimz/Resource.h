// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Collectable.h"
#include "Resource.generated.h"

/**
 * 
 */
UCLASS()
class SWOIMZ_API AResource : public ACollectable
{
	GENERATED_BODY()
	
public:
	AResource();
	virtual void NotifyActorBeginOverlap(AActor* otherActor) override;
	
	int32 ResourceValue;
	
};
