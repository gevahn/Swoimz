// Fill out your copyright notice in the Description page of Project Settings.

#include "Swoimz.h"
#include "Swoim.h"
#include "SwoimerAIMovementI.h"


FVector USwoimerAIMovementI::GetSwoimerAcceleration(class ASwoim* swoimer)
{
	acceleration = FVector(0, 0, 0);
	
	attachedSwoimer = swoimer;

	FVector sep = separate(); //Move away from other swoimers
	FVector ali = align(); // align with other swoimers
	FVector coh = cohesion(); // move towards the CM of the swoim

	sep = sep * SepFactor;
	ali = ali * AliFactor;
	coh = coh * CohFactor;

	if (sep.Size() > 0) {
		acceleration = sep;
	}
	else {
		acceleration = sep + ali + coh;
	}

	if (attachedSwoimer->debugSwoimer) {
		//FlushPersistentDebugLines(GetWorld());
		DrawDebugDirectionalArrow(GetWorld(), attachedSwoimer->GetActorLocation(), attachedSwoimer->GetActorLocation() + sep, 20, FColor(255, 0, 0), true, 0.05, 0, 10);
		DrawDebugDirectionalArrow(GetWorld(), attachedSwoimer->GetActorLocation(), attachedSwoimer->GetActorLocation() + ali, 20, FColor(0, 255, 0), true, 0.05, 0, 10);
		DrawDebugDirectionalArrow(GetWorld(), attachedSwoimer->GetActorLocation(), attachedSwoimer->GetActorLocation() + coh, 20, FColor(0, 0, 255), true, 0.05, 0, 10);
		//UE_LOG(LogTemp, Warning, TEXT("swoimer V %f"), CohFactor);
		//UE_LOG(LogTemp, Warning, TEXT("swoimer A %s"), *acceleration.ToString());
		//	UE_LOG(LogTemp, Warning, TEXT("size of effects array: %d"), ActiveEffects.Num());
	}

	return acceleration;
}

FVector USwoimerAIMovementI::separate()
{

	FVector steer = FVector(0, 0, 0);
	int count = 0;

	for (auto& other : attachedSwoimer->SwoimersArray)
	{
		if (other->IsValidLowLevel()) {
			float d = FVector::Dist(attachedSwoimer->GetActorLocation(), other->GetActorLocation());
			if ((d > 0) && (d < SepDistance))
			{
				steer = steer - (other->GetActorLocation() - attachedSwoimer->GetActorLocation()).GetUnsafeNormal();
				count++;
			}
		}
	}
	if (count > 0) {
		return steer / count;
	}
	else
		return steer;
}


FVector USwoimerAIMovementI::align()
{

	FVector steer = FVector(0, 0, 0);
	int count = 0;

	for (auto& other : attachedSwoimer->SwoimersArray)
	{
		if (other->IsValidLowLevel()) {
			float d = FVector::Dist(attachedSwoimer->GetActorLocation(), other->GetActorLocation());
			if ((d > SepDistance) && (d < AliDistance))
			{

				steer += (other->velocity - attachedSwoimer->velocity).GetSafeNormal();
				count++;
			}
		}
	}

	if (count > 0) {
		return steer / count;
	}
	else
		return steer;
}
FVector USwoimerAIMovementI::cohesion()
{


	FVector steer = FVector(0, 0, 0);
	int count = 0;

	for (auto& other : attachedSwoimer->SwoimersArray)
	{
		if (other->IsValidLowLevel()) {
			float d = FVector::Dist(attachedSwoimer->GetActorLocation(), other->GetActorLocation());
			if ((d > AliDistance) && (d < CohDistance))
			{
				steer = steer + (other->GetActorLocation() - attachedSwoimer->GetActorLocation()).GetUnsafeNormal();
				count++;
			}
		}
	}

	if (count > 0) {
		return steer / count;
	}
	else {
		//Destroy();
		return steer;
	}
}
