// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponet.h"
#include "TankPlayerController.h"
#include "Runtime/Engine/Classes/Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	AimingComnponent = GetPawn()->FindComponentByClass<UTankAimingComponet>();
}

void ATankAIController::Tick(float Deltatime)
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ensure(PlayerPawn)) { return; }

	MoveToActor(PlayerPawn, AcceptanceRadius);

	AimingComnponent->AimtAt(PlayerPawn->GetActorLocation());
	if (AimingComnponent->GetFiringstate() == EFiringStatus::Locked)
	{
		AimingComnponent->Fire();
	}
}
