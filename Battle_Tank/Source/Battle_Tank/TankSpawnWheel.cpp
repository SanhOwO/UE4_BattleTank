// Fill out your copyright notice in the Description page of Project Settings.


#include "TankSpawnWheel.h"

// Sets default values
ATankSpawnWheel::ATankSpawnWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MassWheelsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassWheelsConstraint"));
	SetRootComponent(MassWheelsConstraint);
	

	Mass = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mass"));
	MassWheelsConstraint->SetupAttachment(MassWheelsConstraint);

	Wheels = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheels"));
	Wheels->SetupAttachment(MassWheelsConstraint);

	
}

// Called when the game starts or when spawned
void ATankSpawnWheel::BeginPlay()
{
	Super::BeginPlay();

	if (GetAttachParentActor()) {
		UE_LOG(LogTemp, Warning, TEXT("Not NUll"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("NULL"));
	}
}

// Called every frame
void ATankSpawnWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

