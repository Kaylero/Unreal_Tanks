// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponet.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UTankAimingComponet::UTankAimingComponet()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTankAimingComponet::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UTankAimingComponet::Initialise(UTankBarrel* TankBarrel, UTankTurret *TankTurret)
{	
	if (!TankBarrel || !TankTurret) { return; }

	Barrel = TankBarrel;
	Turret = TankTurret;
}

void UTankAimingComponet::AimtAt(FVector HitLocation)
{
	if (!Barrel) { return; }
	if (!Turret) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity,
		StartLocation, HitLocation, LaunchSpeed, false, 0, 0,
		ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto BarrelLocation = Barrel->GetComponentLocation();

		MoveBarrelTowards(AimDirection);
	}

}

void UTankAimingComponet::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > FireRateInSeconds;

	UE_LOG(LogTemp, Warning, TEXT("??"));

	if (ensure(Barrel && isReloaded && ProjectileBlueprint))
	{
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
																	  Barrel->GetSocketLocation(FName("Projectile")),
																	  Barrel->GetSocketRotation(FName("Projectile")));

		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();
	}
}

void UTankAimingComponet::MoveBarrelTowards(FVector AimDirection)
{
	if (!Barrel) { return; }
	if (!Turret) { return; }

	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}



