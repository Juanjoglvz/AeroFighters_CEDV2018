// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyManager.h"
#include "Enemy.h"


// Sets default values
AEnemyManager::AEnemyManager() : Super(), SeparationLeft(100.f), SeparationRight(100.f), PositionXLeft(200.f), PositionXRight(200.f), MoveLeftSpeed(100.f), MoveRightSpeed(100.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Get references to all the assets we need
	auto BugShipAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Assets/Ships/BugShip'"));
	this->BugShipMesh = BugShipAsset.Object;

}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();

	// Get The references to the borders
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

	// Create the behaviour objects
	this->MoveRightObject = NewObject<UMoveRight>();
	MoveRightObject->SetSpeed(MoveRightSpeed);
	this->MoveLeftObject = NewObject<UMoveLeft>();
	MoveLeftObject->SetSpeed(MoveLeftSpeed);

	// Create the projectile objects
	ShootAtPlayerObject = NewObject<UShootAtPlayerBehaviour>();
	ShootStraightObject = NewObject<UShootStraightBehaviour>();
	MissileObject = NewObject<UMissileBehaviour>();
}

void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyManager::SpawnBug(FVector location,  UMoveBehaviour* Movement, UProjectileBehaviour* ProjectileBehaviour) const
{
	FRotator rotation = FRotator(0.0f, 90.0f, 0.0f);
	AEnemy* EnemySpawned = SpawnEnemy(location, rotation);
	EnemySpawned->SetStaticMesh(this->BugShipMesh);
	EnemySpawned->SetMoveBehaviour(Movement);
	EnemySpawned->SetProjectileBehaviour(ProjectileBehaviour);
}

AEnemy* AEnemyManager::SpawnEnemy(FVector location, FRotator rotation) const
{
	FActorSpawnParameters spawnInfo;
	return GetWorld()->SpawnActor<AEnemy>(location, rotation, spawnInfo);
}

void AEnemyManager::Wave() const
{
	double YpositionLeft{ -1000.f };
	double YpositionRight{ 1000.f };

	for (int i = 0; i < this->NumberLeft; i++, YpositionLeft -= SeparationLeft) {
		SpawnBug(FVector( this->LeftMovableArea->GetActorLocation().X + PositionXLeft, YpositionLeft, 200.f ), 
			this->MoveRightObject, this->ShootStraightObject);
	}

	for (int i = 0; i < this->NumberRight; i++, YpositionRight += SeparationRight) {
		SpawnBug(FVector( this->LeftMovableArea->GetActorLocation().X + PositionXRight, YpositionRight, 200.f ), 
			this->MoveLeftObject, this->MissileObject);
	}
}
