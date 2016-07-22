// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Effect.h"
#include "DiseaseMod.generated.h"

/**
 * 
 */
UCLASS()
class SWOIMZ_API UDiseaseMod : public UEffect
{
	GENERATED_BODY()
	

	UDiseaseMod();
	virtual void BeginPlay() override;

	
	



	void Infect();

	virtual void ApplyEffect(float DeltaTime) override;
	virtual void RemoveEffect() override;

	
	
};
