//  Copyright An-Hung Tai

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// calculate the slippage speed
	// GetForwardVector()instead of GetRightVector()  for low poly tank
	auto SlippageSpeed = FVector::DotProduct(GetForwardVector(), GetOwner()->GetVelocity());
	// work-out the required acceleration this frame to correct
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetForwardVector();
	// calculate and apply sideways
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass()) * CorrectionAcceleration / 2 ; // two tracks
	TankRoot->AddForce(CorrectionForce);
	
}

void UTankTrack::SetThrottle(float Throttle)
{
	// -GetRightVector() instead of GetForwardVector() because of low poly tank
	auto ForceApplied = (-GetRightVector()) * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}