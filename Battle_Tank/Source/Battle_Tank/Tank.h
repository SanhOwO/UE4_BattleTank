// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Projectile.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingCompoment.h"
#include "TankMoveComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLE_TANK_API ATank : public APawn
{
	GENERATED_BODY()

private:

	UTankBarrel* Barrel = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnyWhere, Category = "Health")
	int32 CurrentHealth = StartingHealth;

protected:
	UPROPERTY(BlueprintReadOnly)
	UTankMoveComponent* TankMoveComponent = nullptr;

public:
	// Sets default values for this pawn's properties
	ATank();
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetTankHealth() const;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	FTankDelegate OnDeath;
};
