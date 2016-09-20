// Fill out your copyright notice in the Description page of Project Settings.

#include "Swoimz.h"
#include "Resource.h"
#include "Swoim.h"
#include "SwoimController.h"
#include "Hive.h"


AResource::AResource()
{
	ResourceValue = 100;
}

void AResource::NotifyActorBeginOverlap(AActor* otherActor) {
	ASwoim* testSwoimer = Cast<ASwoim>(otherActor);
	//UE_LOG(LogTemp, Warning, TEXT("swoimer overlapping %s"), *(otherActor->GetName()));
	if (testSwoimer) {
		UE_LOG(LogTemp, Warning, TEXT("collecting resource"));
		testSwoimer->SwoimController->ControllingHive->Resource += ResourceValue;
		Destroy();
	}

}
