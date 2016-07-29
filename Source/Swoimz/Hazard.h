// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Hazard.generated.h"

UCLASS()
class SWOIMZ_API AHazard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHazard();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Effect")
		TSubclassOf<class UEffect>  WhichEffect;


	UPROPERTY(EditAnywhere, Category = "Effect")
		UParticleSystem* WhichParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float timeToLive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float powerLevel;

	void ApplyEffect(class ASwoim* swoimer);



private:
	//box componenet to spawn in
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Box", meta = (AllowPrivateACcess = "true"))
		class UBoxComponent* AreaBox;
	
};
