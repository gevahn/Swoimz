// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class SWOIMZ_API Effect : public UObject
{
public:
	Effect();
	~Effect();

	UParticleSystem* EffectParticle;

	float TimeToLive;

	virtual void ApplyEffect(class ASwoim* swoimer);
	virtual void RemoveEffect(class ASwoim* swoimer);
};
