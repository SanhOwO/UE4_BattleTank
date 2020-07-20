// Fill out your copyright notice in the Description page of Project Settings.


#include "Wheel.h"

UWheel::UWheel()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UWheel::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UWheel::OnHit);
}

void UWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveWheel();
	ApplySidewayForce();
	CurrentThrottle = 0.f;
}

void UWheel::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	

}


void UWheel::ApplySidewayForce()
{
	//修复飘逸 把轮子的力传给主体
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector(); //speed / time
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; //
	TankRoot->AddForce(CorrectionForce);
}	

void UWheel::SetWheel(float w)
{
	//限制速度只能是-1至1
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + w, -1, 1);
	//DriveWheel(CurrentThrottle);
}

void UWheel::DriveWheel()
{
	auto ForceApply = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());	//查看 类查看器
	TankRoot->AddForceAtLocation(ForceApply, ForceLocation);
}
