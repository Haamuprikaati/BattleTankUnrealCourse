// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "BattleTank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!GetPawn()) return;
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();

}
void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		//Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}
}

void ATankPlayerController::OnPossessedTankDeath()
{
	StartSpectatingOnly();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; } //eg. if not possessing
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector OutHitLocation; //Out parameter
	bool bGotHitLocation = GetSightRayHitLocation(OutHitLocation);
	if (bGotHitLocation) //Has "side-effect", is going to linetrace
	{	
		AimingComponent->AimAt(OutHitLocation);
	}
	
}

//Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	//Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	//UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString());
	//Deproject the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (ensure(GetLookDirection(ScreenLocation, LookDirection)))
	{
		//Line trace along that look direction and see what we hit
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; //To be discarded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		CameraWorldLocation, 
		LookDirection
		);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	/*DebugTest
	const static FName TraceTag = TEXT("TraceTag");
	GetWorld()->DebugDrawTraceTag = TraceTag;
	FCollisionQueryParams Params(TraceTag);
	*/

	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	FCollisionQueryParams Params(NAME_None, false, GetPawn());
	if (ensure(GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Camera,
		Params)
		))
		{
			OutHitLocation = HitResult.Location;
			return true;
		}
		OutHitLocation = FVector(0);
		return false; //Line Trace didn't succeed
}