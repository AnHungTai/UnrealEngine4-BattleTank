//  Copyright An-Hung Tai
#include "TankBarrel.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0, +1.0);
	auto ElevationChange = RelativeSpeed * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;

	// low poly tank need to use roll instead of pitch to elevate barrel
	// beause of the pivot point direction
	auto RawNewElevation = RelativeRotation.Roll + ElevationChange;
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegree, MaxElevationDegree);
	SetRelativeRotation(FRotator(0.0, 0.0, Elevation));
}
