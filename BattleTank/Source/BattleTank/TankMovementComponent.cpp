// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initilize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	LeftTrack->SetThrottle(Throw * MovingMultiplier);
	RightTrack->SetThrottle(Throw * MovingMultiplier);
}

void UTankMovementComponent::IntendMoveBackward(float Throw)
{
	LeftTrack->SetThrottle(-Throw * MovingMultiplier);
	RightTrack->SetThrottle(-Throw * MovingMultiplier);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	LeftTrack->SetThrottle(Throw * TurningMultiplier);
	RightTrack->SetThrottle(-Throw * TurningMultiplier);
}

void UTankMovementComponent::IntendTurnLeft(float Throw)
{
	LeftTrack->SetThrottle(-Throw * TurningMultiplier);
	RightTrack->SetThrottle(Throw * TurningMultiplier);
}