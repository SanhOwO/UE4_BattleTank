// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Wheel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLE_TANK_API UWheel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
private:
	UWheel();
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
public:
	//-1 to 1
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetWheel(float Wheel);
	
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 400000.f; //40tone 1g acceleration
};
