// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerLaser.h"
#include "Engine.h"


// Sets default values
APlayerLaser::APlayerLaser() : Super()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Get StaticMesh associated with this projectile 
	auto StaticMeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Assets/Projectile/BasicShot.BasicShot'"));

	if (StaticMeshAsset.Succeeded())
		SetStaticMeshAsset(StaticMeshAsset.Object);

	SetSpeed(550.f);
}

// Called when the game starts or when spawned
void APlayerLaser::BeginPlay()
{
	Super::BeginPlay();
	StaticMesh->SetWorldScale3D(FVector(5.f, 5.f, 2.f));
	StaticMesh->SetRelativeScale3D(FVector(5.f, 5.f, 2.f));
}

void APlayerLaser::ProjectileBehaviour(float DeltaTime)
{
}
