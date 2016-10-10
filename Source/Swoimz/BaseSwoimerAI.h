// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "BaseSwoimerAI.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SWOIMZ_API UBaseSwoimerAI : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseSwoimerAI();

	// Called when the game starts
	virtual void BeginPlay() override;

	virtual FVector GetSwoimerAcceleration(class ASwoim* swoimer);

	float DeltaTime;

	class ASwoim * attachedSwoimer;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		
	
};
