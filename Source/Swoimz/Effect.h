// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Effect.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SWOIMZ_API UEffect : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEffect();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	UParticleSystem* EffectParticle;

	float timeToLive;

	FString name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float powerLevel;

	class ASwoim* swoimer;

	virtual void ApplyEffect(float DeltaTime);
	virtual void RemoveEffect();
	
};
