// Copyright An-Hung Tai

#include "SprungWheel.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Mass Wheel Constraint"));
	SetRootComponent(MassWheelConstraint);

	Mass = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mass"));
	Mass->SetupAttachment(MassWheelConstraint);

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->SetupAttachment(MassWheelConstraint);

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	if (GetAttachParentActor())
	{

	}
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

