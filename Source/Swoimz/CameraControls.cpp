// Fill out your copyright notice in the Description page of Project Settings.

#include "Swoimz.h"
#include "CameraControls.h"


// Sets default values
ACameraControls::ACameraControls()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->TargetArmLength = 1000.0f; // The camera follows at this distance behind the character	
	CameraBoom->AddLocalOffset(FVector(-1, 0, 2));
	CameraBoom->bUsePawnControlRotation = false; // Rotate the arm based on the controller

												 // Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->AttachTo(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

// Called when the game starts or when spawned
void ACameraControls::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraControls::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	FVector CameraLocation;
	FRotator CameraDirection;
	FVector mouseLocation, mouseDirection;
	FVector moveCameraBy;
	float mouseX, mouseY;
	int32 viewportX, viewportY;

	//UE_LOG(LogTemp, Warning, TEXT("testing swoim %s"), *(center).ToString());
	//UE_LOG(LogTemp, Warning, TEXT("swoim is controlled by %s"), *Controller->GetStateName().ToString());
	//UE_LOG(LogTemp, Warning, TEXT("swoim is controlled"));
	//APlayerController* playerController = (APlayerController*)Controller;// = World->GetFirstPlayerController();
	APlayerController* playerController = UGameplayStatics::GetPlayerController(this, playerIndex);
	playerController->DeprojectMousePositionToWorld(mouseLocation, mouseDirection);
	playerController->GetPlayerViewPoint(CameraLocation, CameraDirection);

	playerController->GetMousePosition(mouseX, mouseY);
	playerController->GetViewportSize(viewportX, viewportY);

	if (viewportX - mouseX < 10)
	{
		SetActorLocation(FVector(0, 600, 0) * DeltaTime + GetActorLocation());

	}
	if (mouseX<10)
	{
		SetActorLocation(FVector(0, -600, 0) * DeltaTime + GetActorLocation());

	}
	if (viewportY - mouseY<10)
	{
		SetActorLocation(FVector(-600, 0, 0) * DeltaTime + GetActorLocation());
	}
	if (mouseY<10)
	{
		SetActorLocation(FVector(600, 0, 0) * DeltaTime + GetActorLocation());
	}
}

// Called to bind functionality to input
void ACameraControls::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	// Camera Zoom
	InputComponent->BindAxis("Zoom", this, &ACameraControls::ZoomCamera);


}

void ACameraControls::ZoomCamera(float AxisValue) {

	CameraBoom->TargetArmLength = CameraBoom->TargetArmLength + AxisValue;
}
