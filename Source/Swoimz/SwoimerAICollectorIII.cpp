// Fill out your copyright notice in the Description page of Project Settings.

#include "Swoimz.h"
#include "SwoimerAICollectorIII.h"
#include "Resource.h"
#include "Swoim.h"



FVector USwoimerAICollectorIII::GetSwoimerAcceleration(class ASwoim* swoimer)
{
	attachedSwoimer = swoimer;
	if (targetToCollect == NULL || targetToCollect->IsPendingKillOrUnreachable())
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
