// Fill out your copyright notice in the Description page of Project Settings.

#include "Swoimz.h"
#include "Hive.h"
#include "CameraControls.h"
#include "SwoimzGameMode.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"



ASwoimzGameMode::ASwoimzGameMode()
{
	UE_LOG(LogTemp, Warning, TEXT("SwoimzGameMode"));
}

void ASwoimzGameMode::BeginPlay()
{
	Super::BeginPlay();

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	
	SetCurrentState(ESwoimzPlayState::EPlaying);
	UE_LOG(LogTemp, Warning, TEXT("SwoimzGameMode"));
	
	PlayerOneController = Cast<ACameraControls>(UGameplayStatics::GetPlayerPawn(this, 0));
	/*PlayerOneHive = Cast<AHive>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerTwoHive = Cast<AHive>(UGameplayStatics::GetPlayerPawn(this, 1));*/
	UE_LOG(LogTemp, Warning, TEXT("%p"), PlayerOneController->playerHive);
	UE_LOG(LogTemp, Warning, TEXT("%p"), PlayerOneController->playerHive->EnemyHive);

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

void ASwoimzGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//UE_LOG(LogTemp, Warning, TEXT("ticking health player1:%d, player2:%d "), PlayerOneHive->CurrentHealth, PlayerTwoHive->CurrentHealth);
	if (PlayerOneController->playerHive->CurrentHealth <= 0)
	{
		SetCurrentState(ESwoimzPlayState::EGameOver);
	}
	if (PlayerOneController->playerHive->EnemyHive->CurrentHealth <= 0)
	{
		SetCurrentState(ESwoimzPlayState::EWon);
	}
}


ESwoimzPlayState ASwoimzGameMode::GetCurrentState() const
{
	return CurrentState;
}

void ASwoimzGameMode::SetCurrentState(ESwoimzPlayState NewState)
{
	CurrentState = NewState;
}