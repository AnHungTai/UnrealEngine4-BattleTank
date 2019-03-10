// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile(float Speed)
{
	// FVector(0.0, -1.0, 0.0) instead of FVector::ForwardVector 
	// because the vector is for barrel direction, low poly tank modified.
	ProjectileMovement->SetVelocityInLocalSpace(FVector(0.0, -1.0, 0.0) * Speed);
	ProjectileMovement->Activate();

	UE_LOG(LogTemp, Warning, TEXT("firing at launch speed: %f!"), Speed);
}