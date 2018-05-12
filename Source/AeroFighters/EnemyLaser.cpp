// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyLaser.h"
#include "Engine.h"


// Sets default values
AEnemyLaser::AEnemyLaser() : Super(), Direction { -150.f, 0.f, 0.f }
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Get StaticMesh associated with this projectile 
	auto StaticMeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Assets/Projectile/EnemyShot.EnemyShot'"));
	
	if (StaticMeshAsset.Succeeded())
		SetStaticMeshAsset(StaticMeshAsset.Object);
	
	SetSpeed(450.f);
}

// Called when the game starts or when spawned
void AEnemyLaser::BeginPlay()
{
	Super::BeginPlay();

	// Scale the StaticMesh
	StaticMesh->SetWorldScale3D(FVector(5.f, 5.f, 2.f));
	StaticMesh->SetRelativeScale3D(FVector(5.f, 5.f, 2.f));
}

void AEnemyLaser::ProjectileBehaviour(float DeltaTime)
{
	// Rotate towards the direction
	StaticMesh->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f), false, nullptr, ETeleportType::TeleportPhysics);

	// The projectile moves towards player
	FVector NewLocation = StaticMesh->GetComponentLocation() + (Direction * GetSpeed() * DeltaTime * 0.0001f);
	NewLocation.Z = 200.f;
	StaticMesh->SetWorldLocation(NewLocation);
}
