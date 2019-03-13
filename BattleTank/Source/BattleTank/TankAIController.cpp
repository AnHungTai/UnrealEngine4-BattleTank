// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Runtime/Engine/Classes/Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());
	
	if (!PlayerTank) { return; }

	// move toward the player
	MoveToActor(PlayerTank, AcceptanceRadius);

	// aim toward the player
	ControlledTank->AimAt(PlayerTank->GetActorLocation());
	
	ControlledTank->Fire();
}