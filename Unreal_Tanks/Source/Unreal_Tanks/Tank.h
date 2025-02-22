// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class UNREAL_TANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	ATank();
	UFUNCTION(BlueprintPure)
	float GetHealthPercent();

protected:
	virtual void BeginPlay() override;

public:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	FTankDelegate OnDeath;

	UPROPERTY(EditDefaultsOnly)
	float StartingHealth = 100.0f;
	float CurrentHealth;
};