// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankMovementComponent;
class UTankAimingComponet;
class AProjectile;
class UTankBarrel;
class UTankTurret;

UCLASS()
class UNREAL_TANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	virtual void BeginPlay() override;
	UTankAimingComponet* TankAimingComponent = nullptr;
	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;

public:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void AimtAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;
	UFUNCTION(BlueprintCallable)
	void Fire();
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000;
	UPROPERTY(EditDefaultsOnly)
	float FireRateInSeconds = 3;
	double LastFireTime = 0;

private:
	UTankBarrel* Barrel = nullptr;
};