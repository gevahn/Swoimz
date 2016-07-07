// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Collectable.generated.h"

UCLASS()
class SWOIMZ_API ACollectable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectable();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void NotifyActorBeginOverlap(AActor* otherActor) override;
	
	// the effect to generate
	UPROPERTY(EditAnywhere, Category = "Effect")
		TSubclassOf<class UEffect>  WhichEffect;

	UPROPERTY(EditAnywhere, Category = "Effect")
		UParticleSystem* WhichParticle;

private:
	//box componenet to spawn in
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Box", meta = (AllowPrivateACcess = "true"))
		class UBoxComponent* CollectableBox;



};
