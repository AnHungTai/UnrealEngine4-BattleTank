//  Copyright An-Hung Tai

#include "Projectile.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/DamageType.h"
// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false;

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

	RecoilForce = CreateDefaultSubobject<URadialForceComponent>(FName("Recoil Force"));
	RecoilForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	LaunchSound = CreateDefaultSubobject<UAudioComponent>(FName("Launch Sound"));
	LaunchSound->AttachToComponent(LaunchBlast, FAttachmentTransformRules::KeepRelativeTransform);

	ExplosionSound = CreateDefaultSubobject<UAudioComponent>(FName("Explosion Sound"));
	ExplosionSound->AttachToComponent(ImpactBlast, FAttachmentTransformRules::KeepRelativeTransform);
	ExplosionSound->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::LaunchProjectile(float LaunchSpeed)
{
	if (!ensure(ProjectileMovement)) { return; }
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * LaunchSpeed);
	ProjectileMovement->Activate();
	RecoilForce->FireImpulse();

	LaunchSound->SetRelativeLocation(GetRootComponent()->GetOwner()->GetActorLocation());
	LaunchSound->Play();
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	ExplosionForce->FireImpulse();
	ExplosionSound->Play();

	// destroy CollisionMesh
	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();

	UGameplayStatics::ApplyRadialDamageWithFalloff
	(
		this,
		ProjectileBaseDamage,
		ProjectileMinimumDamage,
		GetActorLocation(),
		(ExplosionForce->Radius) * FullDamageRangeFraction,
		ExplosionForce->Radius,
		DamageFalloffRatio,
		UDamageType::StaticClass(),
		TArray<AActor*>() // damage all actor
	);

	// destroy Actor
	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AProjectile::OnTimeExpire, DestroyDelay, false);
}

void AProjectile::OnTimeExpire()
{
	Destroy();
}