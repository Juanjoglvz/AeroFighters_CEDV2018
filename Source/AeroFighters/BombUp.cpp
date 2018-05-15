// Fill out your copyright notice in the Description page of Project Settings.

#include "BombUp.h"


ABombUp::ABombUp() : Super()
{
	PrimaryActorTick.bCanEverTick = true;

	auto StaticMeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));

	if (StaticMeshAsset.Succeeded())
		SetStaticMeshAsset(StaticMeshAsset.Object);
}

void ABombUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABombUp::CollisionAction(APlayerCharacter* Character)
{
	if (Character)
	{
		Character->IncreaseBombs();
	}
}
