// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLE_TANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
protected:
	//APlayerController* PlayerController;
	//AI离目标的最近距离
	UPROPERTY(EditAnyWhere, Category = "Setup")
	float AcceptanceRadius = 30.f;

public:


private:
	virtual void BeginPlay() override;
	virtual void Tick(float) override;
	virtual void SetPawn(APawn* InPawn) override;

};