// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "SwoimzGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SWOIMZ_API ASwoimzGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	ASwoimzGameMode();


	virtual void BeginPlay() override;
	
	
protected:
	/* The widget class */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> HUDWidgetClass;
	
	/* The instacne of the widget*/
	UPROPERTY()
	class UUserWidget* CurrentWidget;
};
