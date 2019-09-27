// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Turn(float RelativeSpeed)
{
	//Turn the turret right amount this frame
	//Given a max turn speed, and the frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto TurnChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewRotation = RelativeRotation.Yaw + TurnChange;

	SetRelativeRotation(FRotator(0, NewRotation, 0));
	UE_LOG(LogTemp, Warning, TEXT("%f"), NewRotation);
}