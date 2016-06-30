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
	
}



void USpeedMod::ApplyEffect(float DeltaTime) {
	UE_LOG(LogTemp, Warning, TEXT("applying effect"));
	swoimer->maxspeed += powerLevel;
	timeToLive -= DeltaTime;
	if (timeToLive < 0) {
		RemoveEffect();
	}
	UGameplayStatics::SpawnEmitterAttached(EffectParticle, swoimer->GetMesh());
}
void USpeedMod::RemoveEffect() {
	swoimer->ActiveEffects.Remove(this);	
}