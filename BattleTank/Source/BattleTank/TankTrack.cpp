// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	// -GetRightVector() instead of GetForwardVector() because of low poly tank
	auto ForceApplied = (-GetRightVector()) * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}