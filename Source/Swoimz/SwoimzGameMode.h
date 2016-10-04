// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "SwoimzGameMode.generated.h"

/**
*
*/
UENUM(BlueprintType)
enum class ESwoimzPlayState
{
	EPlaying,
	EGameOver,
	EWon,
	EUnknown
};


UCLASS()
class SWOIMZ_API ASwoimzGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	ASwoimzGameMode();

	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintPure, Category = "State")
		ESwoimzPlayState GetCurrentState() const;

	void SetCurrentState(ESwoimzPlayState NewState);
	


protected:
	/* The widget class */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD", Meta = (BlueprintProtected = "true"))
		TSubclassOf<class UUserWidget> HUDWidgetClass;

	/* The instacne of the widget*/
	UPROPERTY()
		class UUserWidget* CurrentWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hive")
	AHive* PlayerOneHive;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hive")
	AHive* PlayerTwoHive;

private:
	ESwoimzPlayState CurrentState;
};


