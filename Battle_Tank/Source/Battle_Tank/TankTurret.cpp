// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Eleate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = RelativeSpeed * MaxDegreePerSecond * GetWorld()->GetTimeSeconds();
	auto NewElevation = GetRelativeRotation().Yaw + ElevationChange;
	SetRelativeRotation(FRotator(0, NewElevation,0));
	//UE_LOG(LogTemp, Warning, TEXT("Turret: %f "), ElevationChange);
}
