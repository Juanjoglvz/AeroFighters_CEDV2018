// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicEnemyPawn.h"
#include "Engine.h"

ABasicEnemyPawn::ABasicEnemyPawn()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Get StaticMesh associated with this enemy and set it
	auto StaticMeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Assets/Ships/spaceshipBasic.spaceshipBasic'"));
	
	if (StaticMeshAsset.Succeeded())
		SetStaticMeshAsset(StaticMeshAsset.Object);
}

void ABasicEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
}

void ABasicEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

