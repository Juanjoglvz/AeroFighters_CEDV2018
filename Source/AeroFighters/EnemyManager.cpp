// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyManager.h"
#include "Enemy.h"


// Sets default values
AEnemyManager::AEnemyManager() : Super()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Get references to all the assets we need
	auto BugShipAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Assets/Ships/BugShip'"));
	this->BugShipMesh = BugShipAsset.Object;

	//Create the behaviour objects
	this->MoveRightObject = MakeShared<MoveRight>(1000.f);

}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();

	Wave0();

}

void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyManager::SpawnEnemy(FVector location, FRotator rotation) const
{
	FActorSpawnParameters spawnInfo;
	auto EnemySpawned = GetWorld()->SpawnActor<AEnemy>(location, rotation, spawnInfo);
	EnemySpawned->SetStaticMesh(this->BugShipMesh);
	EnemySpawned->SetMoveBehaviour(this->MoveRightObject);
}

void AEnemyManager::Wave0() const
{
	SpawnEnemy(FVector(300.f, -550.0f, 200.f), FRotator(0.0f, 90.0f, 0.0f));
	SpawnEnemy(FVector(300.f, -650.0f, 200.f), FRotator(0.0f, 90.0f, 0.0f));
	SpawnEnemy(FVector(300.f, -750.0f, 200.f), FRotator(0.0f, 90.0f, 0.0f));
	SpawnEnemy(FVector(300.f, -850.0f, 200.f), FRotator(0.0f, 90.0f, 0.0f));
	SpawnEnemy(FVector(300.f, -950.0f, 200.f), FRotator(0.0f, 90.0f, 0.0f));
}
