// Fill out your copyright notice in the Description page of Project Settings.

#include "Swoimz.h"
#include "SwoimerAICollectorII.h"
#include "Resource.h"
#include "Swoim.h"



AResource* USwoimerAICollectorII::GetResourceToCollect()
{
	
	UWorld* const World = attachedSwoimer->GetWorld();

	if (World) {
		AResource* toCollect = NULL;
		float size = INFINITY;
		for (TActorIterator<AResource>itr(World); itr; ++itr) {
			if (!itr) continue;
			if (!itr->IsValidLowLevel()) continue;
			if ((itr->GetActorLocation() - attachedSwoimer->GetActorLocation()).Size() < size)
			{
				toCollect = *itr;
			}
		}
		return toCollect;
	}
	else
	{
		return NULL;
	}

}