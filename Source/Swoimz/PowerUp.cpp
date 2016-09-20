// Fill out your copyright notice in the Description page of Project Settings.

#include "Swoimz.h"
#include "PowerUp.h"
#include "Swoim.h"
#include "Effect.h"



void APowerUp::NotifyActorBeginOverlap(AActor* otherActor) {
	ASwoim* testSwoimer = Cast<ASwoim>(otherActor);
	//UE_LOG(LogTemp, Warning, TEXT("swoimer overlapping %s"), *(otherActor->GetName()));
	if (testSwoimer) {
		UE_LOG(LogTemp, Warning, TEXT("applying effect"));
		UEffect* buff = Cast<UEffect>(WhichEffect.GetDefaultObject());
		buff->swoimer = testSwoimer;
		buff->timeToLive = 100;
		buff->EffectParticle = WhichParticle;
		buff->powerLevel = 1000;
		testSwoimer->ActiveEffects.Add(buff);
		Destroy();
	}

}