// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	virtual void Tick(float DeltaSeconds) override;

	bool IsDead() const;

private:

	APawn* PlayerPawn;

	/*UPROPERTY(EditDefaultsOnly, Category = "AI Stuff")
	float AcceptanceRadius = 200.f;*/

	UPROPERTY(EditAnywhere, Category = "AI Stuff")
	class UBehaviorTree* AIBehavior;



};
