// Fill out your copyright notice in the Description page of Project Settings.

#include "StraightProjectile.h"
#include "Engine.h"


// Sets default values
AStraightProjectile::AStraightProjectile() : Super()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Get StaticMesh associated with this projectile 
	auto StaticMeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Assets/Projectile/BasicShot.BasicShot'"));
	SetStaticMeshAsset(StaticMeshAsset.Object);
	S
	SetSpeed(5.f);
}

// Called when the game starts or when spawned
void AStraightProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStraightProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Go Straight Movement
	FVector NewLocation = StaticMesh->GetComponentLocation() + (StaticMesh->GetForwardVector() * GetSpeed() * DeltaTime);
	StaticMesh->SetWorldLocation(NewLocation);
	StaticMesh->SetWorldRotation(FRotator(90.f, 0.f, 0.f));
}

void AStraightProjectile::Clone()
{
	
}

