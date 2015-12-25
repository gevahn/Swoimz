// Fill out your copyright notice in the Description page of Project Settings.

#include "Swoimz.h"
#include "SwoimzGameMode.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"


ASwoimzGameMode::ASwoimzGameMode()
{
	UE_LOG(LogTemp, Warning, TEXT("GameMode"));
}

void ASwoimzGameMode::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("GameMode"));

	if (HUDWidgetClass != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("HUDWidgetClass"));
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (CurrentWidget != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("CurrentWidget"));
			CurrentWidget->AddToViewport();
		}
	}

}