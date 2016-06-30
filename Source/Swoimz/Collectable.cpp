// Fill out your copyright notice in the Description page of Project Settings.

#include "Swoimz.h"
#include "Collectable.h"
#include "Swoim.h"
#include "Effect.h"

// Sets default values
ACollectable::ACollectable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;


	// create the box for spawn volume
	CollectableBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollectableBox"));
	RootComponent = CollectableBox;
}

// Called when the game starts or when spawned
void ACollectable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollectable::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ACollectable::NotifyActorBeginOverlap(AActor* otherActor) {
	ASwoim* testSwoimer = Cast<ASwoim>(otherActor);
	UE_LOG(LogTemp, Warning, TEXT("swoimer overlapping %s"), *(otherActor->GetName()));
	if (testSwoimer) {
		UE_LOG(LogTemp, Warning, TEXT("applying effect"));
		UEffect* buff = Cast<UEffect>(WhichEffect.GetDefaultObject());
		buff->swoimer = testSwoimer;
		buff->timeToLive = 100;
		buff->EffectParticle = WhichParticle;
		buff->powerLevel = 1000;
		testSwoimer->ActiveEffects.Add(buff);
		
	}
	Destroy();
}

