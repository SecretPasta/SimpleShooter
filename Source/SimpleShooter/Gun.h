// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
  USkeletalMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, Category = "Gun Stuff")
	class	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere, Category = "Gun Stuff")
	class	UParticleSystem* HitPoint;

	UPROPERTY(EditAnywhere, Category = "Gun Stuff")
	class USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere, Category = "Gun Stuff")
	class USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = "Gun Stuff")
	float MaxRange = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Gun Stuff")
	float Damage = 10.f;

	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);

	AController* GetOwnerController() const;
};
