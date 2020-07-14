// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingCompoment.h"

// Sets default values for this component's properties
UTankAimingCompoment::UTankAimingCompoment()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UTankAimingCompoment::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
/*void UTankAimingCompoment::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}*/



void UTankAimingCompoment::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) {
		UE_LOG(LogTemp, Error, TEXT("No Barriel Found"));
		return;
	}
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bHaveAimSolution) {
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel_TurretToward(AimDirection);


		auto TankName = GetOwner()->GetName();
		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: Aim Sol Found"), Time);
	}
	else {
		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: No Aim Sol Found"), Time);
	}
}


void UTankAimingCompoment::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	if (!BarrelToSet) return;
	Barrel = BarrelToSet;
}

void UTankAimingCompoment::SetTurretReference(UTankTurret* TurretToSet)
{
	if (!TurretToSet) return;
	Turret = TurretToSet;
	//UE_LOG(LogTemp, Error, TEXT("Turret: %s "), *Turret->GetName());
}

void UTankAimingCompoment::MoveBarrel_TurretToward(FVector AimDirection)
{
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto TurretRotation = Turret->GetForwardVector().Rotation();

	auto AimAsRotator = AimDirection.Rotation();
	auto Barrel_DeltaRotator = AimAsRotator - BarrelRotation;
	auto Turret_DeltaRotator = AimAsRotator - TurretRotation;

	Barrel->Eleate(Barrel_DeltaRotator.Pitch);
	Turret->Eleate(Turret_DeltaRotator.Yaw);
	
	UE_LOG(LogTemp, Error, TEXT("Turret: %s, AimRoatter: %s "), *TurretRotation.ToString(),*AimAsRotator.ToString());
}

