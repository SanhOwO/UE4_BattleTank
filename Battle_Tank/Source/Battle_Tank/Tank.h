// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingCompoment.h"
#include "TankMoveComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//class UTankBarrel;
class AProjectile;

UCLASS()
class BATTLE_TANK_API ATank : public APawn
{
	GENERATED_BODY()

private:

	//UPROPERTY(EditAnyWhere,Category = Setup)
	//UClass* ProjectileBluePrint;		
	//TSubclassOf<AProjectile> ProjectileBluePrint; 

	UTankBarrel* Barrel = nullptr;

	//int ReloadTime = 3;
	//int LastTime = 0;


protected:
	//UPROPERTY(BlueprintReadOnly)
	//UTankAimingCompoment* TankAimingConpoment = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UTankMoveComponent* TankMoveComponent = nullptr;

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	//void AimAt(FVector HitLocation);
	
	//可以再蓝图被调用
	/*UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);*/
	//UFUNCTION(BlueprintCallable)
	//void Fire();
};
