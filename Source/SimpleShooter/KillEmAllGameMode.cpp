// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "GameFramework/Pawn.h"

void AKillEmAllGameMode::PawnKilld(APawn* PawnKilled)
{
	Super::PawnKilld(PawnKilled);

	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController != nullptr) {
		PlayerController->GameHasEnded(nullptr, false);
	}


	//UE_LOG(LogTemp,Warning, TEXT("Pawn killed!!!"));
}
