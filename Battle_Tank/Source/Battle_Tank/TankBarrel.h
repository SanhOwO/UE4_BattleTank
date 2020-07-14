// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLE_TANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//-1������½��ٶȣ�+1����
	void Eleate(float RelativeSpeed);

private: 
	UPROPERTY(EditAnyWhere, Category = Setup)
	float MaxDegreePerSecond = 0.01f;
	UPROPERTY(EditAnyWhere, Category = Setup)
	float MaxElevationDegree = 30.f;
	UPROPERTY(EditAnyWhere, Category = Setup)
	float MinElevationDegree = -10.f;
};
