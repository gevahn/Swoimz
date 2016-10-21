// Fill out your copyright notice in the Description page of Project Settings.

#include "Swoimz.h"
#include "SwoimerAIAttacker.h"
#include "Swoim.h"
#include "SwoimController.h"




FVector USwoimerAIAttacker::GetSwoimerAcceleration(class ASwoim* swoimer)
{
	attachedSwoimer = swoimer;
	
	UE_LOG(LogTemp, Warning, TEXT("swoimers Attacking"));
	TArray<ASwoim*> targetSwoimers;
	UE_LOG(LogTemp, Warning, TEXT("swoimers Attacking %d other swoimz"), targetSwoimers.Num());
	for (TActorIterator<ASwoimController>itr(attachedSwoimer->GetWorld()); itr; ++itr) {
		if (!itr) continue;
		if (!itr->IsValidLowLevel()) continue;
		float distanceToSwoim = (itr->center - attachedSwoimer->SwoimController->center).Size();
		if (distanceToSwoim >= 0) {
			UE_LOG(LogTemp, Warning, TEXT("testing swoim %s"), *(itr->center).ToString());
			UE_LOG(LogTemp, Warning, TEXT("testing swoim %s"), *(itr->GetName()));
			UE_LOG(LogTemp, Warning, TEXT("testing swoim at %f"), distanceToSwoim);
		}
		if (distanceToSwoim > 0 && distanceToSwoim < attachedSwoimer->SwoimController->attackRadius) {
			targetSwoimers.Append(itr->SwoimersArray);
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("swoimers Attacking %d other swoimz"), targetSwoimers.Num());
	if (targetSwoimers.Num() == 0)
	{
		if ((Lane[LaneIndex] - attachedSwoimer->GetActorLocation()).Size() < 50 && LaneIndex<Lane.Num())
		{
			LaneIndex++;
		}
		return (Lane[LaneIndex] - attachedSwoimer->GetActorLocation()).GetSafeNormal()*attachedSwoimer->CenFactor;
	}
	
	int32 indexToAttack = FMath::RandRange(0, targetSwoimers.Num() - 1);
	//UE_LOG(LogTemp, Warning, TEXT("swoimers Attacking swoimer at %d"), indexToAttack);
	targetSwoimer = targetSwoimers[indexToAttack];

	return (targetSwoimer->GetActorLocation() - attachedSwoimer->GetActorLocation()).GetSafeNormal()*attachedSwoimer->CenFactor;
	
}
