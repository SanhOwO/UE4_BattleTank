// Fill out your copyright notice in the Description page of Project Settings.


#include "Wheel.h"

UWheel::UWheel()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UWheel::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	//修正飘逸 把单纯给轮子的力 分给主体
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto CorrectionAcceleration = - SlippageSpeed / DeltaTime * GetRightVector(); //速度除以time
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; //两个轮子
	TankRoot->AddForce(CorrectionForce);
}

void UWheel::SetWheel(float wheel)
{
	auto ForceApply = GetForwardVector() * wheel * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());	//查看 类查看器
	TankRoot->AddForceAtLocation(ForceApply, ForceLocation);
}
