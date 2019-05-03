// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponet.generated.h"

UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UNREAL_TANKS_API UTankAimingComponet : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable)
	void Initialise(UTankBarrel* TankBarrel, UTankTurret *TankTurret);

	// Sets default values for this component's properties
	UTankAimingComponet();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	EFiringStatus FiringState = EFiringStatus::Aiming;
	

public:
	void AimtAt(FVector WorldSpaceAim);
	UFUNCTION(BlueprintCallable)
	void Fire();

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;
	float LaunchSpeed = 4000;
	UPROPERTY(EditDefaultsOnly)
	float FireRateInSeconds = 3;
	double LastFireTime = 0;

	void MoveBarrelTowards(FVector AimDirection);

};
