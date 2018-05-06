// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyProjectile.h"

// Sets default values
AEnemyProjectile::AEnemyProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void AEnemyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check if the projectile has to be destroyed
	if (StaticMesh->GetComponentLocation().X < BottomMovableArea->GetActorLocation().X)
	{
		this->Destroy();
	}

	// The basic movement (falling) is the same for all enemy projectile types
	FVector NewLocation = StaticMesh->GetComponentLocation() + (StaticMesh->GetForwardVector() * GetSpeed() * DeltaTime);
	StaticMesh->SetWorldLocation(NewLocation);
	//StaticMesh->SetWorldRotation(FRotator(90.f, 0.f, 0.f));
}

