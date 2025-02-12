// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTankController.h"
#include "Tank.h"

void AMyTankController::BeginPlay() {
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingCompoment>();
	if (ensure(AimingComponent)) 
		FoundAimingComponent(AimingComponent);
	else
		UE_LOG(LogTemp, Warning, TEXT("No Aiming Component 12"));
	UE_LOG(LogTemp, Warning, TEXT("Player Controller Begin Play"));
}

void AMyTankController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardCorsshair();
}

void AMyTankController::AimTowardCorsshair() {
	if (!GetOwner()) { return; }
	FVector OutHitLocation;
	if (GetSightRayHitLoaction(OutHitLocation)) {
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation： %s"), *OutHitLocation.ToString());
	}
}
	

bool AMyTankController::GetSightRayHitLoaction(FVector& OutHitLocation) const{
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);//获得视口的长宽
	auto ScreenLocation = FVector2D(ViewPortSizeX * CrosshairXLocation, ViewPortSizeY * CrosshairYLocation);
	
	FVector WorldDirection;
	if (GetLookDirection(ScreenLocation, WorldDirection)) {
		if (GetLookVectorHitLocation(WorldDirection, OutHitLocation)) {
			GetPawn()->FindComponentByClass<UTankAimingCompoment>()->AimAt(OutHitLocation);
		}
			
	}

	OutHitLocation = FVector(1.0);
	return true;
}

bool AMyTankController::GetLookVectorHitLocation(FVector LookDirection, FVector& Hitlocation) const {
	FHitResult Hit;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto Endlocation = StartLocation + (LookDirection*LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
		Hit,
		StartLocation,
		Endlocation,
		ECollisionChannel::ECC_Visibility)) 
	{
		Hitlocation = Hit.Location;
		return true;
	}
	Hitlocation = FVector(0);
	return false;
}

bool AMyTankController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDircetion) const {
	FVector WorldLocation;
	DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDircetion);
	return true;
}

void AMyTankController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto PossesedTank = Cast<ATank>(InPawn);
		if (!ensure(PossesedTank)) { return; }

		PossesedTank->OnDeath.AddUniqueDynamic(this, &AMyTankController::OnPossedTankDeath);
	}
}

void AMyTankController::OnPossedTankDeath()
{
	if (!ensure(GetPawn())) { return; }
	StartSpectatingOnly();
}
