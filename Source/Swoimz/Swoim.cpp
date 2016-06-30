// Fill out your copyright notice in the Description page of Project Settings.

#include "Swoimz.h"
#include "Swoim.h"
#include "Effect.h"
#include "SwoimController.h"

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
	avoidAhead = FVector(0, 0, 0);

	CurrentHealth = 100;
	MaxHealth = 100;


	mass = 1;

	// Create mesh
	SwarmerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwarmerMesh"));
	RootComponent = SwarmerMesh;

	targetSwoimer = NULL;



}

// Called when the game starts or when spawned
void ASwoim::BeginPlay()
{

	Super::BeginPlay();
	acceleration = FVector(0, 0, 0);

}

// Called every frame
void ASwoim::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (CurrentHealth < 0) return;

	for (auto& effect : ActiveEffects)
	{
		if (effect->IsValidLowLevel()) {
			effect->ApplyEffect(DeltaTime);
		}
	}

	

	FVector NewLocation = GetActorLocation();
	FVector HitLocation;


	UWorld* const World = GetWorld();

	if (SwoimController.IsValid()) {
		center = SwoimController->center;
		center.Z = 300;
		//UE_LOG(LogTemp, Warning, TEXT("SwoimController is Valid"));
	}

	FVector cen = seek(center); //Track mouse

	FVector sep = separate(); //Move away from other swoimers
	FVector ali = align(); // aligin with other swoimers
	FVector coh = cohesion(); // move towards the CM of the swoim
	FVector atk = FVector(0,0,0); // move toward target

	//UE_LOG(LogTemp, Warning, TEXT("swoimer attacking %s"), targetSwoimer);

	if (targetSwoimer != NULL) {
		atk = attack(targetSwoimer);
	}



	FHitResult HitData(ForceInit);

	
	if (TraceAhead(NewLocation, NewLocation + LookAheadDistance * DeltaTime * velocity, World, HitData)) {		
		if (!HitData.GetActor()->GetClass()->IsChildOf(ASwoim::StaticClass())) {
			FVector ImpactNormalVec = HitData.ImpactNormal;

			FVector DirectionToAvoidImpact = ImpactNormalVec - velocity.GetSafeNormal() * FVector::DotProduct(ImpactNormalVec, velocity.GetSafeNormal());
			avoidAhead = DirectionToAvoidImpact.GetSafeNormal() / ((HitData.Distance)*(HitData.Distance));
			//UE_LOG(LogTemp, Warning, TEXT("mesh ahead, avoid at dir X %f"), avoid.X);
			//UE_LOG(LogTemp, Warning, TEXT("mesh ahead, avoid at dir Y %f"), avoid.Y);
			//UE_LOG(LogTemp, Warning, TEXT("mesh ahead, avoid at dir Z %f"), avoid.Z);
			//UE_LOG(LogTemp, Warning, TEXT("mesh ahead, distance %f"), HitData.Distance);
		}

	}

	FVector avoidClosest = FVector(0, 0, 0);
	//if (ActorGetDistanceToCollision(NewLocation, ECollisionChannel::ECC_WorldStatic, avoidClosest) > 0) {
	//	if (avoidClosest.Size() < 200){
	//		avoidClosest = NewLocation - avoidClosest;
	//	}
	//}
	//center = center + 30 * DeltaTime*FVector(-FMath::Sin(DeltaTime), FMath::Cos(DeltaTime), 0);

	sep = sep * SepFactor;
	ali = ali * AliFactor;
	coh = coh * CohFactor;
	cen = cen * CenFactor;
	atk = atk * AtkFactor;
	FVector avoid = (avoidAhead)* AvoFactor1 + avoidClosest * AvoFactor2;

	acceleration = acceleration + sep + ali + coh + cen + avoid + atk;

	avoidAhead = avoidAhead / LookAheadDecay;

	if (acceleration.Size() > Forcelimit) {
		acceleration = acceleration.GetUnsafeNormal() * Forcelimit;
	}

	

	

	
	velocity = (NewLocation - lastX) * DeltaTime / lastDt + acceleration * (DeltaTime + lastDt) / 2 * DeltaTime;

	if (velocity.Size() > Speedlimit) {
		velocity = velocity.GetSafeNormal() * Speedlimit;
	}
	//if (velocity.Size() < 0.3 * Speedlimit) {
	//	velocity = velocity.GetSafeNormal() * 0.3 * Speedlimit;
	//}

	//UE_LOG(LogTemp, Warning, TEXT("swoimer is at %s"), *lastX.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("lastDt %f"), lastDt);
	NewLocation = NewLocation + velocity;
		
	lastX = GetActorLocation();
	lastDt = DeltaTime;

	
	

	FHitResult* SweepHitData = &HitData; 

	if (!SetActorLocation(NewLocation, true, SweepHitData)) {
		//velocity = velocity - 2 * FVector::DotProduct(SweepHitData->ImpactNormal, velocity) * SweepHitData->ImpactNormal;		
		acceleration = 2 * (FVector::DotProduct(SweepHitData->ImpactNormal, velocity) + 800) * SweepHitData->ImpactNormal;
	}
	else {
		acceleration = FVector(0, 0 ,0);
	}
	SetActorRotation(velocity.Rotation() + FRotator(-90, 0, 0));
	//UE_LOG(LogTemp, Warning, TEXT("swoimer is at %s"), *this->GetActorLocation().ToString());
	


}

void ASwoim::NotifyActorBeginOverlap(AActor* otherActor) {
	ASwoim* testSwoimer = Cast<ASwoim>(otherActor);
	if (testSwoimer && !testSwoimer->IsPendingKill()) {
		if (SwoimController != testSwoimer->SwoimController){
			//UE_LOG(LogTemp, Warning, TEXT("swoimer overlapping %s"), *(otherActor->GetName()));
			testSwoimer->CurrentHealth = testSwoimer->CurrentHealth - SwoimersArray.Num();
			if (testSwoimer->CurrentHealth < 0) {
				testSwoimer->PrimaryActorTick.bCanEverTick = false;
				testSwoimer->GetMesh()->SetSimulatePhysics(true);
				testSwoimer->SwoimersArray.Remove(testSwoimer);
				testSwoimer->SwoimController->SwoimersArray.Remove(testSwoimer);
				testSwoimer->SwoimController->NumberOfSwoimers -= 1;
				UE_LOG(LogTemp, Warning, TEXT("swoimer %s died"), *(otherActor->GetName()));
			}
			SparkOnOverlap();
		}
	}
}

void ASwoim::SparkOnOverlap_Implementation(){
	UE_LOG(LogTemp, Warning, TEXT("spark!"));
}

FVector ASwoim::separate()
{

	FVector steer = FVector(0, 0, 0);
	//int count = 0;
	//char buffer[33];

	for (auto& other : SwoimersArray)
	{
		if (other->IsValidLowLevel()){
			float d = FVector::Dist(GetActorLocation(), other->GetActorLocation());
			if ((d > 0) && (d < SepDistance))
			{
				steer = steer - (other->GetActorLocation() - GetActorLocation());
			}
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
		if (other->IsValidLowLevel()){
			float d = FVector::Dist(GetActorLocation(), other->GetActorLocation());
			if ((d > 0) && (d < AliDistance))
			{

				steer += other->velocity;

			}
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
		if (other->IsValidLowLevel()){
			float d = FVector::Dist(GetActorLocation(), other->GetActorLocation());
			if ((d > 0) && (d < CohDistance))
			{

				steer += other->GetActorLocation();

			}
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


bool ASwoim::TraceAhead(const FVector& Start, const FVector& End, UWorld* World, FHitResult& HitOut) {
	if (!World)
	{
		return false;
	}
	bool ReturnPhysMat = false;
	FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true, this);
	TraceParams.bTraceComplex = true;
	TraceParams.bReturnPhysicalMaterial = ReturnPhysMat;
	TraceParams.AddIgnoredActor(this);

	ECollisionChannel CollisionChannel = ECollisionChannel::ECC_WorldStatic;
	//Re-initialize hit info
	HitOut = FHitResult(ForceInit);

	//Trace!
	World->LineTraceSingleByChannel(
		HitOut,		//result
		Start,	//start
		End, //end
		CollisionChannel, //collision channel
		TraceParams
		);

	//Hit any Actor?
	return (HitOut.GetActor() != NULL);

}

FVector ASwoim::avoid(FHitResult& HitData) {
	// Implement this
	
	return FVector(0, 0, 0);
}

FVector ASwoim::attack(ASwoim* targetSwoimer) {
	//UE_LOG(LogTemp, Warning, TEXT("swoimer attacking"));
	return targetSwoimer->GetActorLocation() - GetActorLocation();
	
}