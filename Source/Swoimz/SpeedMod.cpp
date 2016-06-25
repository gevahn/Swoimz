// Fill out your copyright notice in the Description page of Project Settings.

#include "Swoimz.h"
#include "SpeedMod.h"
#include "Swoim.h"



USpeedMod::USpeedMod()
{

	
}

void USpeedMod::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::SpawnEmitterAttached(EffectParticle, swoimer->GetMesh());
}



void USpeedMod::ApplyEffect(float DeltaTime) {
	swoimer->maxspeed += speedChange;
	timeToLive -= DeltaTime;
	if (timeToLive < 0) {
		RemoveEffect();
	}
}
void USpeedMod::RemoveEffect() {
	swoimer->ActiveEffects.Remove(this);
}