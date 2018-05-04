// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"

// Sets default values
AProjectile::AProjectile() 
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
}

void AProjectile::SetStaticMeshAsset(UStaticMesh* StaticMeshAsset)
{
	StaticMesh->SetStaticMesh(StaticMeshAsset);
	StaticMesh->SetMobility(EComponentMobility::Movable);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// The basic movement (falling) is the same for all projectile types
	FVector NewLocation = StaticMesh->GetComponentLocation() + (StaticMesh->GetForwardVector() * GetSpeed() * DeltaTime);
	StaticMesh->SetWorldLocation(NewLocation);
	StaticMesh->SetWorldRotation(FRotator(90.f, 0.f, 0.f));

	// Each projectile type has a different behaviour
	ProjectileBehaviour();
}

