// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankAimingComponet.h"
#include "Projectile.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

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

public:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void AimtAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);
	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;
	UFUNCTION(BlueprintCallable)
	void Fire();
	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 4000;

private:
	UTankBarrel* Barrel = nullptr;
};
