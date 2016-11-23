// Fill out your copyright notice in the Description page of Project Settings.

#include "Swoimz.h"
#include "Lane.h"
#include "SwoimController.h"
#include <limits>


int FLane::GetClosestPoint(FVector point)
{
	int result = 0;
	float distance = std::numeric_limits<int>::infinity();
	for (size_t i = 0; i < PointArray.Num(); i++)
	{
		float dis = (PointArray[i] - point).Size();
		if (dis < distance)
			result = i;
	}
	return result;
}
