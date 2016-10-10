// Fill out your copyright notice in the Description page of Project Settings.

#include "Swoimz.h"
#include "Swoim.h"
#include "BaseSwoimerAI.h"


// Sets default values for this component's properties
UBaseSwoimerAI::UBaseSwoimerAI()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBaseSwoimerAI::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

FVector UBaseSwoimerAI::GetSwoimerAcceleration(ASwoim * swoimer)
{
	return FVector();
}


// Called every frame
void UBaseSwoimerAI::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

