// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankAimingCompoment.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLE_TANK_API ATank : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnyWhere)
	float LaunchSpeed = 100000; // 100m/s

protected:
	UTankAimingCompoment* TankAimingConpoment = nullptr;

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void AimAt(FVector HitLocation);
	//可以再蓝图被调用
	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UStaticMeshComponent* BarrelToSet);
};
