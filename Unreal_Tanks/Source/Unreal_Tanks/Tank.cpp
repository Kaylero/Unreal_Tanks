// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

float ATank::GetHealthPercent()
{
	return CurrentHealth / StartingHealth;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = StartingHealth;
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float DamageApplied = FMath::Clamp<float>(DamageAmount, 0, CurrentHealth);
	CurrentHealth -= DamageApplied;
	UE_LOG(LogTemp, Warning, TEXT("Damage Applied: %f Current Health:: %f"), DamageApplied, CurrentHealth);
	return DamageAmount;
}

