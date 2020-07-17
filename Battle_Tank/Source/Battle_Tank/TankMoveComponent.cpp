// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMoveComponent.h"

void UTankMoveComponent::InitialWheel(UWheel* Right, UWheel* Left)
{
	if (!Right || !Left) {
		UE_LOG(LogTemp, Error, TEXT("Where is WHeel!!"));
		return;
	}
	RightWheel = Right;
	LeftWheel = Left;
	UE_LOG(LogTemp, Warning, TEXT("%s,%s load"), *Right->GetName(), *Left->GetName());
}

void UTankMoveComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	//¸²¸Ç·½·¨£¬²»½ÐSupe
	
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);

	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendTurnRight(RightThrow);
	//auto Throw = (ForwardThrow > 0 ? 1 : -1);
	IntendMoveForward(ForwardThrow);

	auto Name = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s vectoring is %f"), *Name, ForwardThrow);
}

void UTankMoveComponent::IntendMoveForward(float wheel)
{
	auto Name = GetOwner()->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s move forward %f"), *Name, wheel);
	if (!RightWheel || !LeftWheel)
	{
		UE_LOG(LogTemp, Error, TEXT("Wheel Not Found!!!"));
		return;
	}
	//UE_LOG(LogTemp, Warning, TEXT("%s move %f"),*Name, wheel);
	RightWheel->SetWheel(wheel);
	LeftWheel->SetWheel(wheel);
}

void UTankMoveComponent::IntendTurnRight(float wheel)
{
	auto Name = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s move forward %f"), *Name, wheel);
	if (!RightWheel || !LeftWheel)
	{
		UE_LOG(LogTemp, Error, TEXT("Wheel Not Found!!!"));
		return;
	}
	//UE_LOG(LogTemp, Warning, TEXT("%s,%s load"), *RightWheel->GetName(), *LeftWheel->GetName());
	RightWheel->SetWheel(wheel);
	//LeftWheel->SetWheel(wheel);
}

void UTankMoveComponent::IntendTurnLeft(float wheel)
{
	//auto Name = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s move forward %f"), *Name, wheel);
	if (!RightWheel || !LeftWheel)
	{
		UE_LOG(LogTemp, Error, TEXT("Wheel Not Found!!!"));
		return;
	}
	//UE_LOG(LogTemp, Warning, TEXT("%s,%s load"), *RightWheel->GetName(), *LeftWheel->GetName());
	//RightWheel->SetWheel(wheel);
	LeftWheel->SetWheel(wheel);
}


