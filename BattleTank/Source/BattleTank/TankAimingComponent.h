//  Copyright An-Hung Tai

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// eum for aiming state
UENUM()
enum class EFiringStatus : uint8
{	
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};

// Forward Delaration 
class UTankBarrel;
class UTankTurret;
class AProjectile;

// Hold barrel's properties 
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetAmmoLeft() const;

	void AimAt(FVector HitLocation);

	EFiringStatus GetFiringStatus() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Status")
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	bool IsBarrelMoving();

	void MoveBarrelToward(FVector AimDirection);

	FVector AimDirection;

	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 3500.0;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float ReloadTimeInSecond = 2.0;

	UPROPERTY(EditAnywhere, Category = "Firing")
	int32 AmmoLeft = 20;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AActor>ProjectileBlueprint;

	double LastFireTime = 0.0;
};