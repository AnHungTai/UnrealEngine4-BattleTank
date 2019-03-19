//  Copyright An-Hung Tai

#include "Tank.h"
#include "BattleTank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	float ActualDamage = FMath::Clamp<float>(Damage, 0.0, CurrentHealth);

	CurrentHealth -= ActualDamage;

	UE_LOG(LogTemp, Warning, TEXT("Damage = %f, ActualDamage = %f, CurrentHealth = %f"), Damage, ActualDamage, CurrentHealth);

	return ActualDamage;
}