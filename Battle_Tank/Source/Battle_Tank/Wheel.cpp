// Fill out your copyright notice in the Description page of Project Settings.


#include "Wheel.h"

void UWheel::SetWheel(float wheel)
{
	auto ForceApply = GetForwardVector() * wheel * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());	//�鿴 ��鿴��
	TankRoot->AddForceAtLocation(ForceApply, ForceLocation);
}
