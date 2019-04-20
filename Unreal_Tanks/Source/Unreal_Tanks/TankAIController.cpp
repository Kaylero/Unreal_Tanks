// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankPlayerController.h"
#include "Runtime/Engine/Classes/Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlled tank == null"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("AI Controller possesing: %s"), *(ControlledTank->GetName()));

	ATank* PlayerTank = GetPlayerTank();

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank not found in PlayerController"));
	}

	UE_LOG(LogTemp, Warning, TEXT("PlayerController has tank: %s"), *(GetPlayerTank()->GetName()));	
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	ATankPlayerController* TankPlayerController = Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController());

	if (!TankPlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController not found"));
	}	

	return TankPlayerController->GetControlledTank();
}
