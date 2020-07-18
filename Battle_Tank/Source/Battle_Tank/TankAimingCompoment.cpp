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
	//Super::BeginPlay();
	//FiringState = EFiringState::Aiming;

}

void UTankAimingCompoment::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	int NowTime = FPlatformTime::Seconds();
	bool bIsReloaded = (NowTime - LastTime) < ReloadTime;
	if (bIsReloaded)
		FiringState = EFiringState::Reloading;
	else if(!bIsAimimg())
		FiringState = EFiringState::Locked;
	else
		FiringState = EFiringState::Aiming;
}

bool UTankAimingCompoment::bIsAimimg()
{
	if (!ensure(Barrel)) { UE_LOG(LogTemp, Error, TEXT("No Barriel Found"));  return true; }
	FVector BarrelForwardVector = Barrel->GetForwardVector();
	//UE_LOG(LogTemp, Warning, TEXT("%s, %s"), *BarrelForwardVector.ToString(), *AimDirection.ToString());
	return !BarrelForwardVector.Equals(AimDirection, 0.1);
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
		AimDirection = OutLaunchVelocity.GetSafeNormal();

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

void UTankAimingCompoment::MoveBarrel_TurretToward(FVector HitDirection)
{
	if (!Barrel || !Turret) {
		return;
	}
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto TurretRotation = Turret->GetForwardVector().Rotation();
	//UE_LOG(LogTemp, Warning, TEXT("%s: TurretRotation"), *TurretRotation.ToString());
	auto AimAsRotator = HitDirection.Rotation();
	auto Barrel_DeltaRotator = AimAsRotator - BarrelRotation;
	auto Turret_DeltaRotator = AimAsRotator - TurretRotation;
	//Turret_DeltaRotator.Yaw = abs(AimAsRotator.Yaw) - TurretRotation.Yaw;



	Barrel->Eleate(Barrel_DeltaRotator.Pitch);
	
	//Alway yaw the shortest way
	if (FMath::Abs(Turret_DeltaRotator.Yaw) < 180) {
		Turret->Eleate(Turret_DeltaRotator.Yaw);
	}
	else {
		Turret->Eleate(-Turret_DeltaRotator.Yaw);
	}
	

	//UE_LOG(LogTemp, Error, TEXT("Turret: %s, AimRoatter: %s "), *TurretRotation.ToString(),*AimAsRotator.ToString());
}

void UTankAimingCompoment::Fire()
{
	//UE_LOG(LogTemp, Warning, TEXT("Try to Fire"));
	if (!ensure(Barrel)) { UE_LOG(LogTemp, Warning, TEXT("Has no Barrel 102 ")); return; }
	if (!ensure(ProjectileBluePrint)) { UE_LOG(LogTemp, Warning, TEXT("Has no Projectile 103 ")); return; }

	int NowTime = FPlatformTime::Seconds();
	//bool bIsReloaded = (NowTime - LastTime) > ReloadTime;

	if (FiringState != EFiringState::Reloading) {
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

EFiringState UTankAimingCompoment::GetFiringState() const
{
	return FiringState;
}
