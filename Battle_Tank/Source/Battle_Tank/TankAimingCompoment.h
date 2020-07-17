// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingCompoment.generated.h"

UENUM()
enum class EFiringState : uint8 {
	Reloading,
	Aiming,
	Locked
};

//前向声明，无法实力，只能使用指针和引用，无需include，节省编译时间
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLE_TANK_API UTankAimingCompoment : public UActorComponent
{
	GENERATED_BODY()

private:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditAnyWhere)

	float LaunchSpeed = 4000.f; // 100m/s
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditAnyWhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBluePrint;

	int ReloadTime = 3;
	int LastTime = 0;
protected:

	UPROPERTY(BlueprintReadOnly, Category = "Satate");
	EFiringState FiringState = EFiringState::Reloading;

public:	
	// Sets default values for this component's properties
	UTankAimingCompoment();

	void AimAt(FVector HitLocation);
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initial(UTankBarrel* Barrel, UTankTurret* Turret);
	void MoveBarrel_TurretToward(FVector);
	UFUNCTION(BlueprintCallable)
	void Fire();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

};
