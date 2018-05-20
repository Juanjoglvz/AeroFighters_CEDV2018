// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include "PlayerProjectile.h"
#include "PlayerLaser.h"
#include "PlayerMissile.h"

// Sets default values
AEnemy::AEnemy() : CameraSpeed{ 150.f, 0.f, 0.f }, PowerupSpawnProbability(0.05), LaserDmg(10), MissileDmg(50), RecordsManagerReference(nullptr)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	auto BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));

	BoxCollision->SetCollisionProfileName(TEXT("OverlapAll"));
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->bGenerateOverlapEvents = true;
	StaticMeshComponent->SetupAttachment(RootComponent);

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlap);
}

void AEnemy::SetPowerupType(TSubclassOf<class APowerup> PowerupType)
{
	this->PowerupType = PowerupType;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	GetRecordsManager();

	// Bind an action to destroy the enemy if the character spawns a bomb
	// The action is a lambda function that destroys the projectile
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetCharacter());
	if (PlayerCharacter != nullptr)
	{
		PlayerCharacter->myDiscardEnemyShootsDelegate.AddDynamic(this, &AEnemy::OnBomb);
	}
}

void AEnemy::GetRecordsManager()
{
	FString RecordsManagerString = FString(TEXT("RecordsManager"));
	for (TActorIterator<AActor> itr(GetWorld()); itr; ++itr)
	{
		if (itr->GetName().Contains(RecordsManagerString))
		{
			this->RecordsManagerReference = Cast<ARecordsManager>(*itr);
			return;
		}
	}
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Move at the same rate as the camera
	FVector NewLocation = GetActorLocation();

	NewLocation += CameraSpeed * DeltaTime;

	if (IsValid(Movement))
	{
		Movement->Move(NewLocation, DeltaTime);
	}

	if (ProjectileBehaviour != nullptr)
	{
		ProjectileBehaviour->Shoot(GetWorld(), this->GetActorLocation(), this->GetActorRotation(), DeltaTime);
	}

	if (NewLocation.Y > 2000.f || NewLocation.Y < -2000.f)
	{
		this->Destroy();
	}

	SetActorLocation(NewLocation);
}

void AEnemy::SetStaticMesh(UStaticMesh* Mesh)
{
	StaticMeshComponent->SetStaticMesh(Mesh);
	StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void AEnemy::SetMoveBehaviour(UMoveBehaviour* Move)
{
	this->Movement = Move;
}

void AEnemy::SetHp(int32 HP)
{
	this->HP = HP;
}

void AEnemy::OnBomb()
{
	RecordsManagerReference.Get()->MyIncreaseScore.ExecuteIfBound(1000);
	this->Destroy();
}

void AEnemy::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		if (OtherActor->GetClass()->IsChildOf(APlayerProjectile::StaticClass()))
		{
			// Reduce health and destroy if less than 0
			if (OtherActor->GetClass()->IsChildOf(APlayerLaser::StaticClass()))
			{
				this->HP -= this->LaserDmg;
			}
			else if (OtherActor->GetClass()->IsChildOf(APlayerMissile::StaticClass()))
			{
				this->HP -= this->MissileDmg;
			}
			if (this->HP < 0)
			{
				//Roll the dice for possible drop
				if (PowerupType.Get() && ((float)rand() / (float)RAND_MAX) < PowerupSpawnProbability)
				{

					GetWorld()->SpawnActor<APowerup>(PowerupType, this->GetActorLocation(), FRotator(0.f, 0.f, 0.f));
				}

   				RecordsManagerReference.Get()->MyIncreaseScore.ExecuteIfBound(1000);
				this->Destroy();
			}


			OtherActor->Destroy();
		}
	}
}