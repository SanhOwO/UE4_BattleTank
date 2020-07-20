

#include "TankAimingCompoment.h"
#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("AI Controller Begin Play"));
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { 
		UE_LOG(LogTemp, Error, TEXT("AI didn't find Player tank")); 
		return; 
	}

	//auto PlayerTank = Cast<ATank>(PlayerPawn);

	MoveToActor(PlayerPawn, AcceptanceRadius);
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingCompoment>();
	AimingComponent->AimAt(PlayerPawn->GetActorLocation());

	if (AimingComponent->GetFiringState() == EFiringState::Locked) {
		AimingComponent->Fire();
	}
		


}


void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto PossesedTank = Cast<ATank>(InPawn);
		if (!ensure(PossesedTank)) { return; }


	}
}

