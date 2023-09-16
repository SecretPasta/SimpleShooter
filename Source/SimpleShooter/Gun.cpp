// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"


// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(Root);
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	MeshComponent->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	
	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr)
		return false;
	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	FVector End = Location + Rotation.Vector() * MaxRange;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
	ShotDirection = -Rotation.Vector();

	return bSuccess;
}

AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return nullptr;

	return OwnerPawn->GetController();
}

void AGun::PullTrigger() {
	UE_LOG(LogTemp, Warning, TEXT("Pew"));
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, MeshComponent, TEXT("MuzzleFlashSocket"));

	FHitResult Hit;
	FVector ShotDirection;
	if (GunTrace(Hit, ShotDirection)) {
		//DrawDebugPoint(GetWorld(), Hit.Location, 20, FColor::Red, true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),HitPoint,Hit.Location,ShotDirection.Rotation());
		
		if (Hit.GetActor() != nullptr) {
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			AController* OwnerController = GetOwnerController();
			Hit.GetActor()->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}
	
	

	//DrawDebugCamera(GetWorld(), Location, Rotation, 90, 2, FColor::Red,true);
}
