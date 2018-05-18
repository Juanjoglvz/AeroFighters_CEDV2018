// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyManager.h"
#include "Enemy.h"


// Sets default values
AEnemyManager::AEnemyManager() : Super(), SeparationLeft(100.f), MoveLeftSpeed(100.f), PositionXLeft(200.f), SeparationRight(100.f),
PositionXRight(200.f), MoveRightSpeed(100.f), SeparationTop(100.f), MoveTopSpeed(100.f), MoveTopMaxWaitingTime(5.f),
StopPosition(200.f), EnemyType(EnemyType::Bug), PowerupType(nullptr), StaticSpawn(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Get references to all the assets we need
	auto BugShipAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Assets/Ships/BugShip'"));
	this->BugShipMesh = BugShipAsset.Object;

	auto ShipAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Assets/Ships/SimpleShip'"));
	this->ShipMesh = ShipAsset.Object;

	auto BomberAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Assets/Ships/SpaceShuttle.SpaceShuttle'"));
	this->BomberMesh = BomberAsset.Object;
	
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
	MoveRightObject->SetUp(MoveRightSpeed, GetWorld(), MoveRightMaxWaitingTime);
	this->MoveLeftObject = NewObject<UMoveLeft>();
	MoveLeftObject->SetUp(MoveLeftSpeed, GetWorld(), MoveLeftMaxWaitingTime);
	this->MoveFromTopObject = NewObject<UMoveFromTop>();
	MoveFromTopObject->SetUp(MoveTopSpeed, GetWorld(), MoveTopMaxWaitingTime, StopPosition);

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
	EnemySpawned->SetPowerupType(PowerupType);
	EnemySpawned->SetHp(20);
}

void AEnemyManager::SpawnShip(FVector location, UMoveBehaviour* Movement, UProjectileBehaviour* ProjectileBehaviour) const
{
	FRotator rotation = FRotator(0.0f, -90.0f, 0.0f);
	AEnemy* EnemySpawned = SpawnEnemy(location, rotation);
	EnemySpawned->SetStaticMesh(this->ShipMesh);
	EnemySpawned->SetMoveBehaviour(Movement);
	EnemySpawned->SetProjectileBehaviour(ProjectileBehaviour);
	EnemySpawned->SetPowerupType(PowerupType);
	EnemySpawned->SetHp(40);
}

void AEnemyManager::SpawnBomber(FVector location, UMoveBehaviour* Movement, UProjectileBehaviour* ProjectileBehaviour) const
{
	FRotator rotation = FRotator(0.0f, 90.0f, 0.0f);
	AEnemy* EnemySpawned = SpawnEnemy(location, rotation);
	EnemySpawned->SetStaticMesh(this->BomberMesh);
	EnemySpawned->SetMoveBehaviour(Movement);
	EnemySpawned->SetProjectileBehaviour(ProjectileBehaviour);
	EnemySpawned->SetPowerupType(PowerupType);
	EnemySpawned->SetHp(80);
}

AEnemy* AEnemyManager::SpawnEnemy(FVector location, FRotator rotation) const
{
	FActorSpawnParameters spawnInfo;
	return GetWorld()->SpawnActor<AEnemy>(location, rotation, spawnInfo);
}

void AEnemyManager::SpawnPowerUp() const
{
	FActorSpawnParameters spawnInfo;
	GetWorld()->SpawnActor<APowerup>(this->PowerupType, FVector(this->TopMovableArea->GetActorLocation().X - 300, 0.f, 200.f), FRotator(0.f, 0.f, 0.f));
}

void AEnemyManager::Wave() const
{
	if (this->PowerupType && this->StaticSpawn)
	{
		SpawnPowerUp();
	}
	double YpositionLeft{ -1000.f };
	double YpositionRight{ 1000.f };
	double YPositionTop{ this->PositionYTop };
	if (this->EnemyType == EnemyType::Bug)
	{
		for (int i = 0; i < this->NumberLeft; i++, YpositionLeft -= SeparationLeft) {
			SpawnBug(FVector(this->LeftMovableArea->GetActorLocation().X + PositionXLeft, YpositionLeft, 200.f),
				this->MoveRightObject, NewObject<UShootStraightBehaviour>());
		}

		for (int i = 0; i < this->NumberRight; i++, YpositionRight += SeparationRight) {
			SpawnBug(FVector(this->LeftMovableArea->GetActorLocation().X + PositionXRight, YpositionRight, 200.f),
				this->MoveLeftObject, NewObject<UShootStraightBehaviour>());
		}
		for (int i = 0; i < this->NumberTop; i++, YPositionTop += SeparationTop) {
			SpawnBug(FVector(this->TopMovableArea->GetActorLocation().X + 300.f, YPositionTop, 200.f),
				this->MoveFromTopObject, NewObject<UShootStraightBehaviour>());
		}
	}
	else if (this->EnemyType == EnemyType::Ship)
	{
		for (int i = 0; i < this->NumberLeft; i++, YpositionLeft -= SeparationLeft) {
			SpawnShip(FVector(this->LeftMovableArea->GetActorLocation().X + PositionXLeft, YpositionLeft, 200.f),
				this->MoveRightObject, NewObject<UShootAtPlayerBehaviour>());
		}

		for (int i = 0; i < this->NumberRight; i++, YpositionRight += SeparationRight) {
			SpawnShip(FVector(this->LeftMovableArea->GetActorLocation().X + PositionXRight, YpositionRight, 200.f),
				this->MoveLeftObject, NewObject<UShootAtPlayerBehaviour>());
		}
		for (int i = 0; i < this->NumberTop; i++, YPositionTop += SeparationTop) {
			SpawnShip(FVector(this->TopMovableArea->GetActorLocation().X + 300.f, YPositionTop, 200.f),
				this->MoveFromTopObject, NewObject<UShootAtPlayerBehaviour>());
		}
	
	}
	else if (this->EnemyType == EnemyType::Bomber)
	{
		for (int i = 0; i < this->NumberLeft; i++, YpositionLeft -= SeparationLeft) {
			SpawnBomber(FVector(this->LeftMovableArea->GetActorLocation().X + PositionXLeft, YpositionLeft, 200.f),
				this->MoveRightObject, NewObject<UMissileBehaviour>());
		}

		for (int i = 0; i < this->NumberRight; i++, YpositionRight += SeparationRight) {
			SpawnBomber(FVector(this->LeftMovableArea->GetActorLocation().X + PositionXRight, YpositionRight, 200.f),
				this->MoveLeftObject, NewObject<UMissileBehaviour>());
		}
		for (int i = 0; i < this->NumberTop; i++, YPositionTop += SeparationTop) {
			SpawnBomber(FVector(this->TopMovableArea->GetActorLocation().X + 300.f, YPositionTop, 200.f),
				this->MoveFromTopObject, NewObject<UMissileBehaviour>());
		}
	}
}
