// Fill out your copyright notice in the Description page of Project Settings.


#include "TankSpawnWheel.h"

// Sets default values
ATankSpawnWheel::ATankSpawnWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MassWheelsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassWheelsConstraint"));
	SetRootComponent(MassWheelsConstraint);
	

	Wheels = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheels"));
	Wheels->SetupAttachment(MassWheelsConstraint);

	
}

// Called when the game starts or when spawned
void ATankSpawnWheel::BeginPlay()
{
	Super::BeginPlay();
	SetupConstraint();
	
}

// Called every frame
void ATankSpawnWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATankSpawnWheel::SetupConstraint()
{
	if (!GetAttachParentActor())return;
	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot)return;
	MassWheelsConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Wheels, NAME_None);
}

