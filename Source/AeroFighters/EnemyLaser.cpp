// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyLaser.h"
#include "Engine.h"


// Sets default values
AEnemyLaser::AEnemyLaser() : Super()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Get StaticMesh associated with this projectile 
	auto StaticMeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Assets/Projectile/BasicShot.BasicShot'"));
	
	if (StaticMeshAsset.Succeeded())
		SetStaticMeshAsset(StaticMeshAsset.Object);
	
	SetSpeed(5.f);
}

// Called when the game starts or when spawned
void AEnemyLaser::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemyLaser::ProjectileBehaviour(float DeltaTime)
{

}
