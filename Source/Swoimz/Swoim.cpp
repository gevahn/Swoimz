// Fill out your copyright notice in the Description page of Project Settings.

#include "Swoimz.h"
#include "Swoim.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)

// Sets default values
ASwoim::ASwoim()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bAllowTickOnDedicatedServer = true;
	PrimaryActorTick.bTickEvenWhenPaused = true;

	velocity = 750 * (FVector(FMath::Rand(), FMath::Rand(), FMath::Rand()));
	acceleration = FVector(0, 0, 0);


	mass = 1;

	// Create mesh
	SwarmerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwarmerMesh"));
	RootComponent = SwarmerMesh;



}

// Called when the game starts or when spawned
void ASwoim::BeginPlay()
{

	Super::BeginPlay();

}

// Called every frame
void ASwoim::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	acceleration = FVector(0, 0, 0);

	FVector NewLocation = GetActorLocation();
	FVector HitLocation;
	//UPrimitiveComponent ** PrimitiveHit;



	//ActorGetDistanceToCollision(GetActorLocation(), ECollisionChannel::ECC_WorldStatic, HitLocation, PrimitiveHit);

	/*FVector2D MousePosition;

	UWorld* const World = GetWorld();
	const ULocalPlayer* LocalPlayer;
	if (World) {
		LocalPlayer = World->GetFirstLocalPlayerFromController();
		if (LocalPlayer && LocalPlayer->ViewportClient)
		{
			MousePosition = LocalPlayer->ViewportClient->GetMousePosition();
		}
	}*/

	UWorld* const World = GetWorld();
	FVector mouseLocation, mouseDirection;
	APlayerController* playerController = World ->GetFirstPlayerController();
	playerController->DeprojectMousePositionToWorld(mouseLocation, mouseDirection);


	/*
	UE_LOG(LogTemp, Warning, TEXT("Mouse pos X %f"), MousePosition.X);
	UE_LOG(LogTemp, Warning, TEXT("Mouse pos Y %f"), MousePosition.Y);*/
	
	
	
	FVector sep = separate();
	FVector ali = align();
	FVector coh = cohesion();

	FVector CameraLocation;
	FRotator CameraDirection;
	playerController->GetPlayerViewPoint(CameraLocation, CameraDirection);
		
	
	
	if (!mouseLocation.ContainsNaN()) {
		float t = CameraLocation.Z / (CameraLocation - mouseLocation).Z;
		center = (mouseLocation - CameraLocation) * t + CameraLocation;
		center.Z = 300;
	}


	FVector cen = seek(center);

	//center = center + 30 * DeltaTime*FVector(-FMath::Sin(DeltaTime), FMath::Cos(DeltaTime), 0);

	UE_LOG(LogTemp, Warning, TEXT("center pos X %f"), center.X);
	UE_LOG(LogTemp, Warning, TEXT("center pos Y %f"), center.Y);
	UE_LOG(LogTemp, Warning, TEXT("center pos Z %f"), center.Z);
	sep = sep * SepFactor;
	ali = ali * AliFactor;
	coh = coh * CohFactor;
	cen = cen * CenFactor;

	acceleration = sep + ali + coh + cen;

	if (acceleration.Size() > Forcelimit) {
		acceleration = acceleration.GetUnsafeNormal() * Forcelimit;
	}

	

	velocity = velocity + acceleration;

	
	

	if (velocity.Size() > Speedlimit) {
		velocity = velocity.GetSafeNormal() * Speedlimit;
	}
	//if (velocity.Size() < 0.3 * Speedlimit) {
	//	velocity = velocity.GetSafeNormal() * 0.3 * Speedlimit;
	//}

	NewLocation = NewLocation + velocity * DeltaTime;

	SetActorLocation(NewLocation,true);
	SetActorRotation(velocity.Rotation() + FRotator(-90, 0, 0));


}

FVector ASwoim::separate()
{

	FVector steer = FVector(0, 0, 0);
	//int count = 0;
	//char buffer[33];

	for (auto& other : SwoimersArray)
	{

		float d = FVector::Dist(GetActorLocation(), other->GetActorLocation());
		if ((d > 0) && (d < SepDistance))
		{
			steer = steer - (other->GetActorLocation() - GetActorLocation());
		}
	}
	/*if (steer.Size() > 0) {
	steer = steer.GetUnsafeNormal() * Speedlimit;
	steer = steer - velocity;
	if (steer.Size() > Forcelimit) {
	steer = steer.GetUnsafeNormal() * Forcelimit;
	}
	}*/
	return steer;
}


FVector ASwoim::align()
{

	float Speedlimit = 10;
	FVector steer = FVector(0, 0, 0);



	for (auto& other : SwoimersArray)
	{

		float d = FVector::Dist(GetActorLocation(), other->GetActorLocation());
		if ((d > 0) && (d < AliDistance))
		{

			steer += other->velocity;

		}
	}
	steer = steer / (SwoimersArray.Num() - 1);
	/*
	if (steer.Size() > 0) {
	steer = steer.GetUnsafeNormal() * Speedlimit;
	steer = steer - velocity;
	if (steer.Size() > Forcelimit) {
	steer = steer.GetUnsafeNormal() * Forcelimit;
	}
	}*/
	return steer;
}
FVector ASwoim::cohesion()
{

	float Speedlimit = 10;
	FVector steer = FVector(0, 0, 0);



	for (auto& other : SwoimersArray)
	{

		float d = FVector::Dist(GetActorLocation(), other->GetActorLocation());
		if ((d > 0) && (d < CohDistance))
		{

			steer += other->GetActorLocation();

		}
	}
	steer = steer / (SwoimersArray.Num() - 1);

	return steer - GetActorLocation();
}

FVector ASwoim::seek(FVector target) {
	FVector desired = target - GetActorLocation();
	/*FVector steer;
	if (desired.Size() > 0) {
	desired = desired.GetUnsafeNormal() * Speedlimit;
	steer = desired - velocity;
	steer = steer.GetSafeNormal();
	if (steer.Size() > Forcelimit) {
	steer = steer.GetUnsafeNormal() * Forcelimit;
	}
	}*/
	return desired;

}

void ASwoim::OnUpCohPressed() {
	float Cohlimit = 100;
	CohFactor = CohFactor + 0.1;
	if (CohFactor > Cohlimit) {
		CohFactor = Cohlimit;
	}
}
void ASwoim::OnDownCohPressed() {
	CohFactor = CohFactor - 0.1;
	if (CohFactor < 0) {
		CohFactor = 0;
	}
}


