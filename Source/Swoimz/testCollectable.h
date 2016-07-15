// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "testCollectable.generated.h"

UCLASS()
class SWOIMZ_API AtestCollectable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AtestCollectable();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
private:
	//box componenet to spawn in
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Box", meta = (AllowPrivateACcess = "true"))
	//class UBoxComponent* CollectableBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Swarmer", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* CollectableMesh;
	
	
};
