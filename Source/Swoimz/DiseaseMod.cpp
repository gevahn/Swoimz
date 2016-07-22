// Fill out your copyright notice in the Description page of Project Settings.

#include "Swoimz.h"
#include "DiseaseMod.h"
#include "Swoim.h"
#include "SwoimController.h"


UDiseaseMod::UDiseaseMod()
{


}

void UDiseaseMod::BeginPlay()
{
	Super::BeginPlay();

}



void UDiseaseMod::Infect()
{

	for (auto& other : swoimer->SwoimersArray)
	{
		if (other->IsValidLowLevel()) {
			float d = FVector::Dist(swoimer->GetActorLocation(), other->GetActorLocation());
			if (d<30)
			{
				other->ActiveEffects.Add(this);
			}
		}
	}

}


void UDiseaseMod::ApplyEffect(float DeltaTime) {
	Infect();
	swoimer->DamageSwoimer(swoimer, powerLevel);
	timeToLive -= DeltaTime;
	if (timeToLive < 0) {
		RemoveEffect();
	}
	UGameplayStatics::SpawnEmitterAttached(EffectParticle, swoimer->GetMesh());
}
void UDiseaseMod::RemoveEffect() {
	swoimer->ActiveEffects.Remove(this);
}
