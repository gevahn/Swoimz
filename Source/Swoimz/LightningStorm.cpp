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

	for (auto& first : OverlappingActors) {
		for (auto& second : OverlappingActors) {
			float d = FVector::Dist(first->GetActorLocation(), second->GetActorLocation());
			if (d > 0 && d < ArcDistance)
			{
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
			UParticleSystemComponent * FiredLightning = UGameplayStatics::SpawnEmitterAttached(LightiningParticle, first->GetMesh());
			FiredLightning->SetBeamTargetPoint(0, second->GetActorLocation(), 0);
		}
	}
}