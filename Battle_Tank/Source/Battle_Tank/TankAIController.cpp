

#include "TankAimingCompoment.h"
#include "TankAIController.h"


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

	GetPawn()->FindComponentByClass<UTankAimingCompoment>()->AimAt(PlayerPawn->GetActorLocation());
	GetPawn()->FindComponentByClass<UTankAimingCompoment>()->Fire();


}

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("AI Controller Begin Play"));	
}