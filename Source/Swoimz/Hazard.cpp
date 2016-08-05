// Fill out your copyright notice in the Description page of Project Settings.

#include "Swoimz.h"
#include "Hazard.h"
#include "Swoim.h"
#include "Effect.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"


// Sets default values
AHazard::AHazard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;


	// create the box for the hazard area
	AreaBox = CreateDefaultSubobject<UBoxComponent>(TEXT("AreaBox"));
	RootComponent = AreaBox;
}

// Called when the game starts or when spawned
void AHazard::BeginPlay()
{
	Super::BeginPlay();
	time = 0;
}

// Called every frame
void AHazard::Tick( float DeltaTime )
{

	Super::Tick( DeltaTime );
	//UE_LOG(LogTemp, Warning, TEXT("deltatime: %f"), DeltaTime);
	if (time <= 0)
	{
		time = 2;
		TArray<AActor*> OverlappingActors;
		GetOverlappingActors(OverlappingActors, ASwoim::StaticClass());
		for (auto& itr : OverlappingActors)
		{
			ASwoim* swoimer = Cast<ASwoim>(itr);
			if (swoimer && swoimer->CurrentHealth>0)
			{
		//		UE_LOG(LogTemp, Warning, TEXT("swoimers on hazard"));
				ApplyEffect(swoimer);
			}
		}
		
	}
	else
	{
		time -= DeltaTime;
	}

}

void AHazard::ApplyEffect(ASwoim* swoimer) {

	bool isEffected = false;
	for (auto& itr : swoimer->ActiveEffects)
	{

		if (itr->name.Equals(name))
		{
			itr->timeToLive = timeToLive;
		//UE_LOG(LogTemp, Warning, TEXT("effect already on"));
			isEffected = true;
			break;
		}

	}
	if (!isEffected)
	{
		//UE_LOG(LogTemp, Warning, TEXT("applying effect"));
		UEffect* effect = Cast<UEffect>(WhichEffect.GetDefaultObject());
		effect->name = name; // not sure.
		effect->swoimer = swoimer;
		effect->timeToLive = timeToLive;
		effect->EffectParticle = WhichParticle;
		effect->powerLevel = powerLevel;
		UGameplayStatics::SpawnEmitterAttached(WhichParticle, swoimer->GetMesh());
		swoimer->ActiveEffects.Add(effect);
	}
}

