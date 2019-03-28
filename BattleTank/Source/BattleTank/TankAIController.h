// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	// how close the AI close to the player
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 5000.0;

	UFUNCTION()
	void OnPossessedTankDeath();

private:
	virtual void BeginPlay() override;
	
	virtual void SetPawn(APawn* InPawn) override;

	virtual void Tick(float DeltaTime) override;
};
