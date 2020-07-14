 // Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Constructor
	TankAimingConpoment = CreateDefaultSubobject<UTankAimingCompoment>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingConpoment->AimAt(HitLocation, LaunchSpeed);
	//auto TankName = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s"), *TankName,*HitLocation.ToString());
}

void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	TankAimingConpoment->SetBarrelReference(BarrelToSet);
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingConpoment->SetTurretReference(TurretToSet);
}

