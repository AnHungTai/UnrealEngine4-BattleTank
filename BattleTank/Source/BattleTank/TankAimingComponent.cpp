//  Copyright An-Hung Tai

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Core/Public/Math/Vector.h"

#define OUT

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }
	if (!Turret) { return; }

	FVector LaunchVelocity(0); // out parameter
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OUT LaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam,
		TArray<AActor*>(),
		true // draw trace line
	);
	if (bHaveAimSolution)
	{
		FVector AimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrelToward(AimDirection);	
	} 
}

void UTankAimingComponent::MoveBarrelToward(FVector AimDirection)
{
	if (!Barrel || !Turret) { return; }
	// low poly tank need to use - GetRightVector() instead of GetForwardVector()
	// beause of the pivot point direction
	auto BarrelRotator = (-Barrel->GetRightVector()).Rotation();
	// where the player is aiming
	auto AimAsRotator = AimDirection.Rotation();
	// the difference of vector between player aiming and barrel
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);

	// turret choose the shortest direction to rotate
	if (FMath::Abs(DeltaRotator.Yaw) < 180.0)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}	
}

