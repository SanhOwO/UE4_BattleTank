// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLE_TANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	//-1是最高下降速度，+1向上
	void Eleate(float RelativeSpeed);

private:
	UPROPERTY(EditAnyWhere, Category = Setup)
		float MaxDegreePerSecond = 0.01f;
};
