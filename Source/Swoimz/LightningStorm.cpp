// Fill out your copyright notice in the Description page of Project Settings.

#include "Swoimz.h"
#include "LightningStorm.h"
#include "Swoim.h"



ALightningStorm::ALightningStorm()
{
	Damage = 5;
	ArcDistance = 100;

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// create the box for spawn volume
	StormBox = CreateDefaultSubobject<UBoxComponent>(TEXT("StormBox"));
	RootComponent = StormBox;

}

void ALightningStorm::BeginPlay()
{
	Super::BeginPlay();
}

void ALightningStorm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors, ASwoim::StaticClass());

	int FireCounter = 0;

	for (auto& first : OverlappingActors) {
		for (auto& second : OverlappingActors) {
			float d = FVector::Dist(first->GetActorLocation(), second->GetActorLocation());
			if (d > 0 && d < ArcDistance && FireCounter < 10)
			{
				FireCounter++;
				Fire(Cast<ASwoim>(first), Cast<ASwoim>(second));
			}

		}
	}

}

void ALightningStorm::Fire(ASwoim* first, ASwoim* second)
{
	if (LightiningParticle != NULL)
	{
		UWorld* const World = GetWorld();
		if (World)
		{
			//LightiningParticle->Get
			UParticleSystemComponent * FiredLightning = UGameplayStatics::SpawnEmitterAtLocation(World,	LightiningParticle, first->GetActorLocation());
			FiredLightning->SetBeamTargetPoint(0, second->GetActorLocation(), 0);
		}
	}
}