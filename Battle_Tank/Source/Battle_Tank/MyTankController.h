// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankAimingCompoment.h"
#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyTankController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLE_TANK_API AMyTankController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingCompoment* AimRef);
	virtual void BeginPlay() override;	//Virtual ���� ����ԭ�е�beginplay ������ʱ����virtual��override
	virtual void Tick(float) override;

private:
	void AimTowardCorsshair();//�ƶ��ڹ� ����׼��λ��
	bool GetSightRayHitLoaction(FVector&) const;
	bool GetLookVectorHitLocation(FVector, FVector&) const;
	bool GetLookDirection(FVector2D, FVector&) const;
	UPROPERTY(EditAnyWhere);
	float CrosshairXLocation = 0.5f;
	UPROPERTY(EditAnyWhere);
	float CrosshairYLocation = 0.3333f;
	UPROPERTY(EditAnyWhere);
	float LineTraceRange = 1000000;
	
};
