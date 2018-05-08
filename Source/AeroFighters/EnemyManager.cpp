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
	this->MoveRightObject = MakeShared<MoveRight>(100.f);
	this->MoveLeftObject = MakeShared<MoveLeft>(100.f);

}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();

	//Get The references to the borders
	FString TopMovableAreaString = FString(TEXT("TopMovableArea"));
	FString BottomMovableAreaString = FString(TEXT("BottomMovableArea"));
	FString RightMovableAreaString = FString(TEXT("RightMovableArea"));
	FString LeftMovableAreaString = FString(TEXT("LeftMovableArea"));
	uint32 i = 0;
	for (TActorIterator<AActor> itr(GetWorld()); itr; ++itr)
	{
		if (TopMovableAreaString.Equals(itr->GetName()))
		{
			this->TopMovableArea = *itr;
			i++;
		}
		else if (BottomMovableAreaString.Equals(itr->GetName()))
		{
			this->BottomMovableArea = *itr;
			i++;
		}
		else if (RightMovableAreaString.Equals(itr->GetName()))
		{
			this->RightMovableArea = *itr;
			i++;
		}
		else if (LeftMovableAreaString.Equals(itr->GetName()))
		{
			this->LeftMovableArea = *itr;
			i++;
		}

		if (i > 3)
		{
			break;
		}
	}


	Wave0();

}

void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyManager::SpawnBug(FVector location,  TSharedPtr<MoveBehaviour> Movement) const
{
	FRotator rotation = FRotator(0.0f, 90.0f, 0.0f);
	AEnemy* EnemySpawned = SpawnEnemy(location, rotation);
	EnemySpawned->SetStaticMesh(this->BugShipMesh);
	EnemySpawned->SetMoveBehaviour(Movement);
}

AEnemy* AEnemyManager::SpawnEnemy(FVector location, FRotator rotation) const
{
	FActorSpawnParameters spawnInfo;
	return GetWorld()->SpawnActor<AEnemy>(location, rotation, spawnInfo);
}

void AEnemyManager::Wave0() const
{
	SpawnBug(FVector(this->LeftMovableArea->GetActorLocation().X + 200, -550.0f, 200.f), this->MoveRightObject);
	SpawnBug(FVector(this->LeftMovableArea->GetActorLocation().X + 200, -650.0f, 200.f), this->MoveRightObject);
	SpawnBug(FVector(this->LeftMovableArea->GetActorLocation().X + 200, -750.0f, 200.f), this->MoveRightObject);
	SpawnBug(FVector(this->LeftMovableArea->GetActorLocation().X + 200, -850.0f, 200.f), this->MoveRightObject);
	SpawnBug(FVector(this->LeftMovableArea->GetActorLocation().X + 200, -950.0f, 200.f), this->MoveRightObject);

	SpawnBug(FVector(this->LeftMovableArea->GetActorLocation().X + 300, 550.0f, 200.f), this->MoveLeftObject);
	SpawnBug(FVector(this->LeftMovableArea->GetActorLocation().X + 300, 650.0f, 200.f), this->MoveLeftObject);
	SpawnBug(FVector(this->LeftMovableArea->GetActorLocation().X + 300, 750.0f, 200.f), this->MoveLeftObject);
	SpawnBug(FVector(this->LeftMovableArea->GetActorLocation().X + 300, 850.0f, 200.f), this->MoveLeftObject);
	SpawnBug(FVector(this->LeftMovableArea->GetActorLocation().X + 300, 950.0f, 200.f), this->MoveLeftObject);
}
