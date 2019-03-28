//  Copyright An-Hung Tai

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// call by the engine when actor damage is dealt
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser) override;

	// return current health as a percentage of starting health
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	FTankDelegate OnDeath;

	void DestroyTank();

private:
	// Sets default values for this pawn's properties
	ATank();

	virtual void BeginPlay() override;

	void OnTimeExpire();

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float StartingHealth = 100.0;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	float CurrentHealth;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float DestroyDelay = 3.0;
};
