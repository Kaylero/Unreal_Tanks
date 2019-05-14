// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponet.h"
#include "TankPlayerController.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/Pawn.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponet>();
}

void ATankAIController::Tick(float Deltatime)
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ensure(PlayerPawn)) { return; }

	MoveToActor(PlayerPawn, AcceptanceRadius);

	AimingComponent->AimtAt(PlayerPawn->GetActorLocation());
	auto State = (int)(AimingComponent->GetFiringstate());
	if (AimingComponent->GetFiringstate() == EFiringStatus::Locked)
	{

		AimingComponent->Fire();
	}
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}

void ATankAIController::OnTankDeath()
{
	GetPawn()->DetachFromControllerPendingDestroy();
}
