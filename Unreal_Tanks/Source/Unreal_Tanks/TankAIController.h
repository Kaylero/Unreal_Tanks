// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankAimingComponet.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponet;



UCLASS()
class UNREAL_TANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	void Tick(float Deltatime) override;
	UPROPERTY(EditAnywhere)
	float AcceptanceRadius = 3000.0;

private:
	UTankAimingComponet* AimingComponent = nullptr;

	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnTankDeath();

};
