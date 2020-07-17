// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "DrawDebugHelpers.h"
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

void UTankAimingCompoment::AimAt(FVector HitLocation)
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
	DrawDebugLine(
		GetWorld(),
		StartLocation,
		HitLocation,
		FColor::Blue,
		false
	);
	if (bHaveAimSolution) {
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		
		MoveBarrel_TurretToward(AimDirection);


		auto TankName = GetOwner()->GetName();
		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%s: Aim Sol Found"), *AimDirection.ToString());
	}
	else {
		///auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: No Aim Sol Found"), Time);
	}
}


void UTankAimingCompoment::Initial(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingCompoment::MoveBarrel_TurretToward(FVector AimDirection)
{
	if (!Barrel || !Turret) {
		return;
	}
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto TurretRotation = Turret->GetForwardVector().Rotation();
	//UE_LOG(LogTemp, Warning, TEXT("%s: TurretRotation"), *TurretRotation.ToString());
	auto AimAsRotator = AimDirection.Rotation();
	auto Barrel_DeltaRotator = AimAsRotator - BarrelRotation;
	auto Turret_DeltaRotator = AimAsRotator - TurretRotation;
	//Turret_DeltaRotator.Yaw = abs(AimAsRotator.Yaw) - TurretRotation.Yaw;
	
		

	Barrel->Eleate(Barrel_DeltaRotator.Pitch);
	Turret->Eleate(Turret_DeltaRotator.Yaw);
	
	//UE_LOG(LogTemp, Error, TEXT("Turret: %s, AimRoatter: %s "), *TurretRotation.ToString(),*AimAsRotator.ToString());
}

void UTankAimingCompoment::Fire()
{
	if (!Barrel) { return; }
	if (!ProjectileBluePrint) { return; }

	int NowTime = FPlatformTime::Seconds();
	bool bIsReloaded = (NowTime - LastTime) > ReloadTime;

	if (bIsReloaded && Barrel) {
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBluePrint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		if (Projectile == NULL)
		{
			UE_LOG(LogTemp, Warning, TEXT("not spawn any projectile"));
			return;
		}
		Projectile->LaunchProjectile(LaunchSpeed);

		LastTime = NowTime;
	}
	//Projectile->LaunchProjectile(1000);

}