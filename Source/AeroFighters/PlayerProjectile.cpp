// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerProjectile.h"


// Sets default values
APlayerProjectile::APlayerProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check if the projectile has to be destroyed
	if (StaticMesh->GetComponentLocation().X > TopMovableArea->GetActorLocation().X)
	{
		this->Destroy();
	}

	// The basic movement (go up) is the same for all player projectile types
	FVector NewLocation = StaticMesh->GetComponentLocation() - (StaticMesh->GetForwardVector() * -1 * GetSpeed() * 100 * DeltaTime);
	StaticMesh->SetWorldLocation(NewLocation);
	//StaticMesh->SetWorldRotation(FRotator(90.f, 0.f, 0.f));
}

