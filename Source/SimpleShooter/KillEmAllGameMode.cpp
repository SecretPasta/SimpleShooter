// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "GameFramework/Pawn.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"

void AKillEmAllGameMode::PawnKilld(APawn* PawnKilled)
{
	Super::PawnKilld(PawnKilled);

	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController != nullptr) {
		EndGame(false);
	}

	for (AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld())) {
		if (!Controller->IsDead())
			return;
	}
	EndGame(true);


	//UE_LOG(LogTemp,Warning, TEXT("Pawn killed!!!"));


}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner) {

	for (AController* Controller : TActorRange<AController>(GetWorld())) {
		bool bIsWinner = (Controller->IsPlayerController() == bIsPlayerWinner);
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}
