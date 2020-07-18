// Fill out your copyright notice in the Description page of Project Settings.


#include "Wheel.h"

UWheel::UWheel()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UWheel::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UWheel::OnHit);
}

void UWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit hti"));
}

void UWheel::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	//修复飘逸 把轮子的力传给主体
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector(); //�ٶȳ���time
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; //��������
	TankRoot->AddForce(CorrectionForce);
}


void UWheel::SetWheel(float wheel)
{
	auto ForceApply = GetForwardVector() * wheel * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());	//查看 类查看器
	TankRoot->AddForceAtLocation(ForceApply, ForceLocation);
}
