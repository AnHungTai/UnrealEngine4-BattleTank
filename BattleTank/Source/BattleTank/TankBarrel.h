//  Copyright An-Hung Tai

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downward speed, and +1 is max up movement
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDegreePerSecond = 45.0;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxElevationDegree = 45.0;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MinElevationDegree = -10.0;

};
