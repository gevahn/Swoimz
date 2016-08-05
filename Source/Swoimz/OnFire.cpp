// Fill out your copyright notice in the Description page of Project Settings.

#include "Swoimz.h"
#include "OnFire.h"
#include "Swoim.h"
#include "SwoimController.h"



UOnFire::UOnFire()
{


}

void UOnFire::BeginPlay()
{
	Super::BeginPlay();
	name = "OnFire";
	UGameplayStatics::SpawnEmitterAttached(EffectParticle, swoimer->GetMesh());
}



void UOnFire::ApplyEffect(float DeltaTime) {
	//swoimer->DamageSwoimer(swoimer, powerLevel);
	swoimer->CurrentHealth -= powerLevel;
	timeToLive -= DeltaTime;
	if (timeToLive < 0) {
		RemoveEffect();
	}
	//UGameplayStatics::SpawnEmitterAttached(EffectParticle, swoimer->GetMesh());
}

void UOnFire::RemoveEffect() {
	swoimer->ActiveEffects.Remove(this);
}