//  Copyright An-Hung Tai

#include "Tank.h"
#include "BattleTank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	float ActualDamage = FMath::Clamp<float>(Damage, 0.0, CurrentHealth);
	CurrentHealth -= ActualDamage;

	if (CurrentHealth <= 0.0)
	{
		OnDeath.Broadcast();
	}

	return ActualDamage;
}

float ATank::GetHealthPercent() const
{
	return CurrentHealth / StartingHealth;
}