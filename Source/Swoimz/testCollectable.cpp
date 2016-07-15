// Fill out your copyright notice in the Description page of Project Settings.

#include "Swoimz.h"
#include "testCollectable.h"


// Sets default values
AtestCollectable::AtestCollectable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollectableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CollectableMesh"));
	RootComponent = CollectableMesh;

}

// Called when the game starts or when spawned
void AtestCollectable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AtestCollectable::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

