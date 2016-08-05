// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Effect.h"
#include "OnFire.generated.h"

/**
 * 
 */
UCLASS()
class SWOIMZ_API UOnFire : public UEffect
{
	GENERATED_BODY()
	UOnFire();
	virtual void BeginPlay() override;





	virtual void ApplyEffect(float DeltaTime) override;
	virtual void RemoveEffect() override;

	
	
};
