// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle_Tank.h"
#include "TankBarrel.h"

void UTankBarrel::Eleate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto ElevationChange = RelativeSpeed * MaxDegreePerSecond * GetWorld()->GetTimeSeconds();
	auto RawNewElevation = GetRelativeRotation().Pitch + ElevationChange;
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegree, MaxElevationDegree);//clamp 最大最小和中间
	//UE_LOG(LogTemp, Warning, TEXT("RelativeSpeed: %f "), RelativeSpeed);
	SetRelativeRotation(FRotator(Elevation, 0, 0));
}
