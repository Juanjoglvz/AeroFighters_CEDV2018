// Fill out your copyright notice in the Description page of Project Settings.

#include "Boss.h"
#include "PlayerProjectile.h"
#include "PlayerLaser.h"
#include "PlayerMissile.h"
#include "EnemyLaser.h"
#include "EnemyMissile.h"
#include "Enemy.h"
#include "MoveRight.h"
#include "MoveLeft.h"
#include "ShootStraightBehaviour.h"


// Sets default values
ABoss::ABoss() : CameraSpeed {150.0f, 0.0f, 0.0f}, Hp{5000}, LaserDmg{10}, MissileDmg{50},
b_Enraged{ false }, b_BugSpawn{ false }, b_LaserCircle{ false }, b_MissileWave{ false },
LTimer{ 0.0f }, LaserTimer{ 0.5 }, MTimer{ 0.0f }, MissileTimer{ 1.f }, BTimer{ 0.f }, BugSpawnTimer{ 1.f },
CurrentLaser{ 0 }, CurrentMissile{ 0 }, BugsSpawned{ 0 }
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	StaticMeshComponent->SetupAttachment(RootComponent);

	auto StaticMeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Assets/Ships/Frigate'"));

	if (StaticMeshAsset.Succeeded())
	{
		StaticMeshComponent->SetStaticMesh(StaticMeshAsset.Object);
		StaticMeshComponent->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
		StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	}
	auto BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	// Changed variables because box collision Component does not seem to be set up correctly
	BoxCollision->RelativeScale3D = FVector(0.5, 2.65, 1.0);
	BoxCollision->SetCollisionProfileName(TEXT("OverlapAll"));
	BoxCollision->SetupAttachment(StaticMeshComponent);
	BoxCollision->bGenerateOverlapEvents = true;

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ABoss::OnOverlap);



	// Get references to all the assets we need
	auto BugShipAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Assets/Ships/BugShip'"));
	this->BugShipMesh = BugShipAsset.Object;
	
}

// Called when the game starts or when spawned
void ABoss::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	NewLocation += CameraSpeed * DeltaTime;

	if (IsValid(Position))
	{
		if (this->GetActorLocation().X > (this->Position->GetActorLocation().X + 550))
		{
			NewLocation.X -= 50 * DeltaTime;
		}
	}



	if (b_BugSpawn && BugsSpawned < 3)
	{
		UMoveRight* MovementRight = NewObject<UMoveRight>();
		MovementRight->SetUp(100.f, GetWorld(), 0.f);
		SpawnBug(FVector{Position->GetActorLocation().X + 350 + BugsSpawned * 50, -1000.f, 200.f}, MovementRight);

		UMoveLeft* MovementLeft = NewObject<UMoveLeft>();
		MovementRight->SetUp(100.f, GetWorld(), 0.f);
		SpawnBug(FVector{ Position->GetActorLocation().X + 350 + BugsSpawned * 50, 1000.f, 200.f }, MovementLeft);


		BugsSpawned++;
	}
	if (b_BugSpawn && BugsSpawned >= 3)
	{
		BugsSpawned = 0;
		b_BugSpawn = false;
	}


	SetActorLocation(NewLocation);

}

// Called to bind functionality to input
void ABoss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABoss::SetPosition(AActor* Position)
{
	this->Position = Position;
}

void ABoss::Enrage()
{
	this->b_Enraged = true;
}

void ABoss::LaserCircle()
{
	this->b_LaserCircle = true;
}

void ABoss::MissileWave()
{
	this->b_MissileWave = true;
}

void ABoss::BugSpawn()
{
	this->b_BugSpawn = true;
}

void ABoss::SpawnBug(FVector Location, UMoveBehaviour* Movement) const
{
	FRotator rotation = FRotator(0.0f, 90.0f, 0.0f);
	FActorSpawnParameters spawnInfo;
	TWeakObjectPtr<AEnemy> EnemySpawned = GetWorld()->SpawnActor<AEnemy>(Location, rotation, spawnInfo);
	EnemySpawned->SetStaticMesh(this->BugShipMesh);
	EnemySpawned->SetMoveBehaviour(Movement);
	EnemySpawned->SetProjectileBehaviour(NewObject<UShootStraightBehaviour>());
	EnemySpawned->SetHp(20);
}

void ABoss::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		if (OtherActor->GetClass()->IsChildOf(APlayerProjectile::StaticClass()))
		{
			// Reduce health and destroy if less than 0
			if (OtherActor->GetClass()->IsChildOf(APlayerLaser::StaticClass()))
			{
				this->Hp -= this->LaserDmg;
			}
			else if (OtherActor->GetClass()->IsChildOf(APlayerMissile::StaticClass()))
			{
				this->Hp -= this->MissileDmg;
			}
			if (this->Hp < 0)
			{
				this->Destroy();
			}


			OtherActor->Destroy();
		}
	}
}
