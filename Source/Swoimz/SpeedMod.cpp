// Fill out your copyright notice in the Description page of Project Settings.

#include "Swoimz.h"
#include "SpeedMod.h"
#include "Swoim.h"
#include "SwoimController.h"



USpeedMod::USpeedMod()
{

	
}

void USpeedMod::BeginPlay()
{
	Super::BeginPlay();
	
}



void USpeedMod::ApplyEffect(float DeltaTime) {
	
	swoimer->Speedlimit = powerLevel;
	timeToLive -= DeltaTime;
	if (timeToLive < 0) {
		RemoveEffect();
	}
	UGameplayStatics::SpawnEmitterAttached(EffectParticle, swoimer->GetMesh());
}
void USpeedMod::RemoveEffect() {
	swoimer->Speedlimit = swoimer->SwoimController->Speedlimit;
	swoimer->ActiveEffects.Remove(this);	
}