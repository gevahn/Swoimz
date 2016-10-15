// Fill out your copyright notice in the Description page of Project Settings.

#include "Swoimz.h"
#include "SwoimerAICollectorI.h"
#include "Resource.h"
#include "Swoim.h"



FVector USwoimerAICollectorI::GetSwoimerAcceleration(class ASwoim* swoimer)
{
	attachedSwoimer = swoimer;
	if (targetToCollect == NULL)
	{
		targetToCollect = GetResourceToCollect();
	}
	if (targetToCollect == NULL)
	{
		return FVector(0, 0, 0);
	}
	targetLocation = targetToCollect->GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("target location %s"), *targetLocation.ToString());
	UE_LOG(LogTemp, Warning, TEXT("name of target %s"), *targetToCollect->GetName());
	//UE_LOG(LogTemp, Warning, TEXT("mesh ahead, avoid at dir Z %f"), avoid.Z);
	return (targetLocation - attachedSwoimer->GetActorLocation()).GetSafeNormal()*attachedSwoimer->CenFactor;
}

AResource* USwoimerAICollectorI::GetResourceToCollect()
{
	float criteria = 0.5;
	UWorld* const World = attachedSwoimer->GetWorld();
	
	if (World) {
		UE_LOG(LogTemp, Warning, TEXT("name of world? %s"), *World->GetName());
		AResource* toCollect = NULL;
		for (TActorIterator<AResource>itr(World); itr; ++itr) {
			if (!itr) continue;
			if (!itr->IsValidLowLevel()) continue;
			toCollect = *itr;
			float rand = FMath::FRandRange(0, 1);
			if (rand > criteria)
			{
				break;
			}
			criteria = criteria*criteria;
		}
		return toCollect;
	}
	else
	{
		return NULL;
	}
	
}


