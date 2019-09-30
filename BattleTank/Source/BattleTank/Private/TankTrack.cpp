// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle)
{

	// TODO Clamp actual throttle value so player cannot overdrive
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

}