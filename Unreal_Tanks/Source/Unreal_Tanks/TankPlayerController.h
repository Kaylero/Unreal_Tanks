// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponet;

UCLASS()
class UNREAL_TANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	void AimTowardsCrosshair();

protected:

	UFUNCTION(BlueprintImplementableEvent)
	void FoundAimingComponent(UTankAimingComponet* AimingComponent);

private:
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector & HitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const;
	virtual void SetPawn(APawn* InPawn) override;
	UFUNCTION()
	void OnTankDeath();
	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000000;
	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5;
	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.333333;

	UTankAimingComponet* TankAimingComponent = nullptr;
};
