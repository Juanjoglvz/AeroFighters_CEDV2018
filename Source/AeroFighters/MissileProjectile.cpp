// Fill out your copyright notice in the Description page of Project Settings.

#include "MissileProjectile.h"
#include "Engine.h"


// Sets default values
AMissileProjectile::AMissileProjectile() : Super()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Get StaticMesh associated with this projectile 
	auto StaticMeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Assets/Projectile/BasicMissile.BasicMissile'"));
	SetStaticMeshAsset(StaticMeshAsset.Object);
	
	SetSpeed(3.f);
}

// Called when the game starts or when spawned
void AMissileProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMissileProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Go Straight Movement
	FVector NewLocation = StaticMesh->GetComponentLocation() + (StaticMesh->GetForwardVector() * GetSpeed() * DeltaTime);
	StaticMesh->SetWorldLocation(NewLocation);
}

void AMissileProjectile::Clone()
{

}

