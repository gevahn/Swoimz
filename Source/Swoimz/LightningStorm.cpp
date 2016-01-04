// Fill out your copyright notice in the Description page of Project Settings.

#include "Swoimz.h"
#include "LightningStorm.h"
#include "Swoim.h"



ALightningStorm::ALightningStorm()
{
	Damage = 5;
	ArcDistance = 100;
	NumOfLights = 10;

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


	TArray<ASwoim*> HitSwoimers;
	for (auto& first : OverlappingActors) {
		for (auto& second : OverlappingActors) {
			float d = FVector::Dist(first->GetActorLocation(), second->GetActorLocation());
			if (d > 0 && d < ArcDistance)
			{
				HitSwoimers.Add(Cast<ASwoim>(second));
			}
		}
	}

	if (HitSwoimers.Num() > 1) {
		int32 CurInt = FMath::RandRange(0, HitSwoimers.Num() - 1);
		int32 NextInt = FMath::RandRange(0, HitSwoimers.Num() - 1);
		for (int i = LightiningsArray.Num(); i < FMath::Min(HitSwoimers.Num(), NumOfLights); i++) {
			LightiningsArray.Add(Fire(HitSwoimers[CurInt], HitSwoimers[NextInt]));
			CurInt = NextInt;
			NextInt = FMath::RandRange(0, HitSwoimers.Num() - 1);

		}
	}
	
		
	

	UE_LOG(LogTemp, Warning, TEXT("LightiningsArray %d"), LightiningsArray.Num());

	bool IsCompeleted = true;
	for (auto& Lightining : LightiningsArray) {
		if (!Lightining->HasCompleted())
		{
			IsCompeleted = false;
		}
	}
	if (IsCompeleted)
	{
		LightiningsArray.Empty();
	}


}

UParticleSystemComponent * ALightningStorm::Fire(ASwoim* first, ASwoim* second)
{
	if (LightiningParticle != NULL)
	{
		UWorld* const World = GetWorld();
		if (World)
		{
			//LightiningParticle->Get
			UParticleSystemComponent * FiredLightning = UGameplayStatics::SpawnEmitterAttached(LightiningParticle, first->GetMesh());
			FiredLightning->SetActorParameter("Target", second);
			return FiredLightning;
		}
	}
	return nullptr;
}