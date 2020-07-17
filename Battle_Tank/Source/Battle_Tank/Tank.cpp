 // Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Constructor
	//TankAimingConpoment = CreateDefaultSubobject<UTankAimingCompoment>(FName("Aiming Component"));
	//TankMoveComponent = CreateDefaultSubobject<UTankMoveComponent>(FName("Movement Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
	//TankAimingConpoment = FindComponentByClass<UTankAimingCompoment>();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

/*void ATank::AimAt(FVector HitLocation)
{
	//if (!ensure(TankAimingConpoment)) { return; }
	//TankAimingConpoment->AimAt(HitLocation, LaunchSpeed);
	//auto TankName = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s"), *TankName,*HitLocation.ToString());
}

void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	if (!BarrelToSet) { return; }
	//TankAimingConpoment->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::Fire()
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
		//Projectile->LaunchProjectile(LaunchSpeed);

		LastTime = NowTime;
	}
	//Projectile->LaunchProjectile(1000);

}
*/
