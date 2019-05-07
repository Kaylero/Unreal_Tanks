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
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UTankAimingComponet::BeginPlay()
{
	Super::BeginPlay();

	LastFireTime = FPlatformTime::Seconds();
	// ...
	
}

void UTankAimingComponet::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	if (!((FPlatformTime::Seconds() - LastFireTime) > FireRateInSeconds))
	{
		FiringState = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringStatus::Aiming;
	}
	else
	{
		FiringState = EFiringStatus::Locked;
	}
}

void UTankAimingComponet::Initialise(UTankBarrel* TankBarrel, UTankTurret *TankTurret)
{	
	if (!TankBarrel || !TankTurret) { return; }

	Barrel = TankBarrel;
	Turret = TankTurret;
}

bool UTankAimingComponet::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	return !Barrel->GetForwardVector().Equals(CurrentAimDirection, 0.01);
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
		CurrentAimDirection = OutLaunchVelocity.GetSafeNormal();
		auto BarrelLocation = Barrel->GetComponentLocation();

		MoveBarrelTowards(CurrentAimDirection);
	}

}

void UTankAimingComponet::Fire()
{

	if (FiringState != EFiringStatus::Reloading)
	{
		if (ensure(Barrel && ProjectileBlueprint))
		{
			AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
																		  Barrel->GetSocketLocation(FName("Projectile")),
																		  Barrel->GetSocketRotation(FName("Projectile")));

			Projectile->LaunchProjectile(LaunchSpeed);

			LastFireTime = FPlatformTime::Seconds();
		}
	}	
}

EFiringStatus UTankAimingComponet::GetFiringstate()
{
	return FiringState;
}

void UTankAimingComponet::MoveBarrelTowards(FVector AimDirection)
{
	if (!Barrel) { return; }
	if (!Turret) { return; }

	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;

	Barrel->Elevate(DeltaRotator.Pitch);
	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
}




