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
	virtual void BeginPlay() override;	//Virtual 函数 覆盖原有的beginplay 声明的时候不用virtual和override
	virtual void Tick(float) override;

private:
	void AimTowardCorsshair();//移动炮管 根据准心位置
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
