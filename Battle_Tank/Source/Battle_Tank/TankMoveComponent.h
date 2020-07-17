// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Wheel.h"
#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMoveComponent.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLE_TANK_API UTankMoveComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable,Category = "Input")
	void IntendMoveForward(float wheel);
	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendTurnRight(float wheel);
	UFUNCTION(BlueprintCallable, Category = "Input"	)
	void IntendTurnLeft(float wheel);
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void InitialWheel(UWheel* Right, UWheel* Left);

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

private:

	UWheel* RightWheel = nullptr;
	UWheel* LeftWheel = nullptr;
};
