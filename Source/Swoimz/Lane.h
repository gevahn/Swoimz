// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Lane.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FLane
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lane")
	FString Name;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lane")
		TArray<FVector> PointArray;

	int GetClosestPoint(FVector point);

	FLane()
	{
		Name = "something";
	}
};