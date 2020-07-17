// Fill out your copyright notice in the Description page of Project Settings.


#include "Wheel.h"

UWheel::UWheel()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UWheel::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	//����Ʈ�� �ѵ��������ӵ��� �ָ�����
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto CorrectionAcceleration = - SlippageSpeed / DeltaTime * GetRightVector(); //�ٶȳ���time
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; //��������
	TankRoot->AddForce(CorrectionForce);
}

void UWheel::SetWheel(float wheel)
{
	auto ForceApply = GetForwardVector() * wheel * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());	//�鿴 ��鿴��
	TankRoot->AddForceAtLocation(ForceApply, ForceLocation);
}
