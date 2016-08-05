// Fill out your copyright notice in the Description page of Project Settings.

#include "Swoimz.h"
#include "Effect.h"


// Sets default values for this component's properties
UEffect::UEffect()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEffect::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}



void UEffect::ApplyEffect(float DeltaTime) {

}
void UEffect::RemoveEffect() {

}