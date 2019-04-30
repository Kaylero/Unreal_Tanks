// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;
/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREAL_TANKS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintCallable)
	void Initialise(UTankTrack* LeftTrack, UTankTrack *RightTrack);

	UFUNCTION(BlueprintCallable)
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable)
	void IntendTurnRight(float Throw);

	void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;


private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
};
