// Fill out your copyright notice in the Description page of Project Settings.

#include "Particles/ParticleSystemComponent.h"
#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

 
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>("Partical_Mesh");
	LaunchBlast->AttachTo(CollisionMesh);    //将粒子效果绑定在根结点上（即ProjectileMesh）
	//LaunchBlast->SetAutoActivate(true);                //创建好就启动

	//LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
		//LaunchBlast->SetupAttachment(CollisionMesh);
	//LaunchBlast->SetAutoActivate(false);



	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false;

	
	//SetRootComponent(LaunchBlast);
	//LaunchBlast->AttachToComponent(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile(float Speed)
{
	ProjectileMovement->Activate();
	UE_LOG(LogTemp, Warning, TEXT("is Firing at %f"), Speed);
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	
}

