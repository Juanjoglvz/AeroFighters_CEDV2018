/* Copyright (C) 2018 Iván García, Juan José Corroto and Javier Córdoba - All Rights Reserved
* You may use, distribute and modify this code under the
* terms of the GNU GPLv3 license.
*
* You should have received a copy of the GNU GPLv3 license with
* this file. If not, please write to: ivan.garcia16@alu.uclm.es
*/

#include "Boss.h"
#include "PlayerProjectile.h"
#include "PlayerLaser.h"
#include "PlayerMissile.h"
#include "EnemyLaser.h"
#include "EnemyMissile.h"
#include "Enemy.h"
#include "MoveRight.h"
#include "MoveLeft.h"
#include "BossAIController.h"
#include "ShootStraightBehaviour.h"


// Sets default values
ABoss::ABoss() : CameraSpeed {150.0f, 0.0f, 0.0f}, Hp{5000}, LaserDmg{10}, MissileDmg{50}, BombDmg{300},
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


	auto BehaviorTreeAsset = ConstructorHelpers::FObjectFinder<UBehaviorTree>(TEXT("BehaviorTree'/Game/Blueprints/BossBT.BossBT'"));

	if (BehaviorTreeAsset.Succeeded())
		BehaviorTree = BehaviorTreeAsset.Object;
	
}

// Called when the game starts or when spawned
void ABoss::BeginPlay()
{
	Super::BeginPlay();

	ABossAIController* AIController = GetWorld()->SpawnActor<ABossAIController>(ABossAIController::StaticClass());
	AIController->Possess(this);

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetCharacter());
	if (PlayerCharacter != nullptr)
	{
		PlayerCharacter->myDiscardEnemyShootsDelegate.AddDynamic(this, &ABoss::OnBomb);
	}
	
}


// Called every frame
void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Only increase the counter that we need
	if (b_BugSpawn)
	{
		BTimer += DeltaTime;
	}
	if (b_LaserCircle)
	{
		LTimer += DeltaTime;
	}
	if (b_MissileWave)
	{
		MTimer += DeltaTime;
	}

	//Move with the camera
	FVector NewLocation = GetActorLocation();
	NewLocation += CameraSpeed * DeltaTime;

	if (IsValid(Position))
	{
		if (this->GetActorLocation().X > (this->Position->GetActorLocation().X + 550))
		{
			NewLocation.X -= 50 * DeltaTime;
		}
	}

	if (b_LaserCircle)
	{
		LaserAttack();
	}

	if (b_MissileWave)
	{
		MissileAttack();
	}

	//Spawn Bugs
	if (b_BugSpawn)
	{
		SpawnBugWave();
	}
	
	SetActorLocation(NewLocation);
}

void ABoss::LaserAttack()
{
	if (LTimer > LaserTimer && CurrentLaser < 1)
	{
		AEnemyLaser* EnemyLaser1 = GetWorld()->SpawnActor<AEnemyLaser>(FVector{ GetActorLocation().X - 160.f, 0.f, 200.f}, FRotator{ 0.f, -90.f, 0.f });
		if (IsValid(EnemyLaser1))
		{
			EnemyLaser1->SetDirection(FVector{ -1.f, 0.f, 0.f });
		}

		LTimer = 0.f;
		CurrentLaser++;
	}
	if (LTimer > LaserTimer && CurrentLaser > 0 && CurrentLaser < 4)
	{
		AEnemyLaser* EnemyLaser1 = GetWorld()->SpawnActor<AEnemyLaser>(FVector{GetActorLocation().X - 160.f + CurrentLaser * 20.f, 100.f * CurrentLaser, 200.f}, FRotator{ 0.f, -90.f, 0.f });
		if (IsValid(EnemyLaser1))
		{
			EnemyLaser1->SetDirection(FVector{ -1.f, CurrentLaser * 0.8f, 0.f }.GetSafeNormal());
		}


		AEnemyLaser* EnemyLaser2 = GetWorld()->SpawnActor<AEnemyLaser>(FVector{ GetActorLocation().X - 160.f + CurrentLaser * 20.f, -100.f * CurrentLaser, 200.f }, FRotator{ 0.f, -90.f, 0.f });
		if (IsValid(EnemyLaser2))
		{
			EnemyLaser2->SetDirection(FVector{ -1.f, -(CurrentLaser * 0.8f), 0.f }.GetSafeNormal());
		}

		LTimer = 0.f;
		CurrentLaser++;
	}
	if (b_Enraged)
	{
		if (LTimer > LaserTimer && CurrentLaser < 6)
		{
			AEnemyLaser* EnemyLaser1 = GetWorld()->SpawnActor<AEnemyLaser>(FVector{ GetActorLocation().X - 160.f + CurrentLaser * 20.f, 100.f * (6 - CurrentLaser), 200.f }, FRotator{ 0.f, -90.f, 0.f });
			if (IsValid(EnemyLaser1))
			{
				EnemyLaser1->SetDirection(FVector{ -1.f, (6 - CurrentLaser) * 0.8f, 0.f }.GetSafeNormal());
			}

			AEnemyLaser* EnemyLaser2 = GetWorld()->SpawnActor<AEnemyLaser>(FVector{ GetActorLocation().X - 160.f + CurrentLaser * 20.f, -100.f * (6 - CurrentLaser), 200.f }, FRotator{ 0.f, -90.f, 0.f });
			if (IsValid(EnemyLaser2))
			{
				EnemyLaser2->SetDirection(FVector{ -1.f, -(6 - CurrentLaser) * 0.8f, 0.f }.GetSafeNormal());
			}

			LTimer = 0.f;
			CurrentLaser++;
		}
		else if (LTimer > LaserTimer && CurrentLaser == 6)
		{
			AEnemyLaser* EnemyLaser1 = GetWorld()->SpawnActor<AEnemyLaser>(FVector{ GetActorLocation().X - 160.f, 0.f, 200.f }, FRotator{ 0.f, -90.f, 0.f });
			if (IsValid(EnemyLaser1))
			{
				EnemyLaser1->SetDirection(FVector{ -1.f, 0.f, 0.f });
			}

			LTimer = 0.f;
			CurrentLaser++;
		}
		else if (LTimer > LaserTimer * 3)
		{
			LTimer = 0.f;
			CurrentLaser = 0;
			b_LaserCircle = false;
		}
	}
	else if(LTimer > LaserTimer * 3 && CurrentLaser > 3)
	{
		LTimer = 0.f;
		CurrentLaser = 0;
		b_LaserCircle = false;
	}
}

void ABoss::MissileAttack()
{
	if (MTimer > MissileTimer && CurrentMissile < 6)
	{
		GetWorld()->SpawnActor<AEnemyMissile>(FVector{ GetActorLocation().X - 100.f, -250.f + CurrentMissile * 100.f, 200.f }, GetActorRotation());
		if (b_Enraged)
		{
			GetWorld()->SpawnActor<AEnemyMissile>(FVector{ GetActorLocation().X + 100.f, -500.f + CurrentMissile * 200.f, 200.f }, GetActorRotation());
		}

		MTimer = 0.f;
		CurrentMissile++;
	}
	if (MTimer > MissileTimer && CurrentMissile >= 6)
	{
		CurrentMissile = 0;
		MTimer = 0.f;
		b_MissileWave = false;
	}
}

void ABoss::SpawnBugWave()
{
	if (BTimer > BugSpawnTimer && BugsSpawned < 3)
	{
		UMoveRight* MovementRight = NewObject<UMoveRight>();
		MovementRight->SetUp(100.f, GetWorld(), 0.f);
		SpawnBug(FVector{ Position->GetActorLocation().X + 350 + BugsSpawned * 50, -1000.f, 200.f }, MovementRight);

		UMoveLeft* MovementLeft = NewObject<UMoveLeft>();
		MovementLeft->SetUp(100.f, GetWorld(), 0.f);
		SpawnBug(FVector{ Position->GetActorLocation().X + 350 + BugsSpawned * 50, 1000.f, 200.f }, MovementLeft);


		BugsSpawned++;
		BTimer = 0.f;
	}
	if (BTimer > BugSpawnTimer && BugsSpawned >= 3)
	{
		if (b_Enraged)
		{
			UMoveRight* MovementRight = NewObject<UMoveRight>();
			MovementRight->SetUp(100.f, GetWorld(), 0.f);
			SpawnBug(FVector{ Position->GetActorLocation().X + 350, -1000.f, 200.f }, MovementRight);
			SpawnBug(FVector{ Position->GetActorLocation().X + 350, -1200.f, 200.f }, MovementRight);

			UMoveLeft* MovementLeft = NewObject<UMoveLeft>();
			MovementLeft->SetUp(100.f, GetWorld(), 0.f);
			SpawnBug(FVector{ Position->GetActorLocation().X + 350, 1000.f, 200.f }, MovementLeft);
			SpawnBug(FVector{ Position->GetActorLocation().X + 350, 1200.f, 200.f }, MovementLeft);
		}
		BugsSpawned = 0;
		BTimer = 0.f;
		b_BugSpawn = false;
	}
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

float ABoss::GetHp()
{
	return this->Hp;
}

void ABoss::OnBomb()
{
	this->Hp -= BombDmg;
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
				// Show widget when the boss is destroyed
				APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetCharacter());
				if (PlayerCharacter != nullptr)
				{
					PlayerCharacter->MyBossDestroyed.ExecuteIfBound();
				}
				this->Destroy();
			}


			OtherActor->Destroy();
		}
	}
}
