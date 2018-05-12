// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAsteroid.h"


AEnemyAsteroid::AEnemyAsteroid() : Super()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	auto StaticMeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Assets/Asteroid/Asteroid1.Asteroid1'"));

	if (StaticMeshAsset.Succeeded())
		StaticMeshComponent->SetStaticMesh(StaticMeshAsset.Object);
}

AAsteroid* AEnemyAsteroid::clone()
{
	return GetWorld()->SpawnActor<AAsteroid>(AEnemyAsteroid::StaticClass(), StaticMeshComponent->GetComponentTransform());
}