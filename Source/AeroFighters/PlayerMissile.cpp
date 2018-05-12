// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerMissile.h"
#include "Enemy.h"
#include "Engine.h"

// Sets default values
APlayerMissile::APlayerMissile() : Super(), LockedEnemy{ nullptr }
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Get StaticMesh associated with this projectile 

	auto StaticMeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Assets/Projectile/PlayerMissile.PlayerMissile'"));


	if (StaticMeshAsset.Succeeded())
		SetStaticMeshAsset(StaticMeshAsset.Object);

	SetSpeed(300.f);
}

// Called when the game starts or when spawned
void APlayerMissile::BeginPlay()
{
	Super::BeginPlay();

	// Resize projectile
	StaticMesh->SetWorldScale3D(FVector(5.f, 5.f, 5.f));
	StaticMesh->SetRelativeScale3D(FVector(5.f, 5.f, 5.f));
}

// The behaviour is to find the nearest enemy and go for it
void APlayerMissile::ProjectileBehaviour(float DeltaTime)
{

	if (LockedEnemy == nullptr)
	{
		float MinimumDistance{ 1000000.f };
		for (TActorIterator<AActor> Iterator(GetWorld()); Iterator; ++Iterator)
		{
			float SubstractInX = StaticMesh->GetComponentLocation().X - Iterator->GetActorLocation().X;
			float SubstractInY = StaticMesh->GetComponentLocation().Y - Iterator->GetActorLocation().Y;
			float Distance = FMath::Sqrt(FMath::Pow(SubstractInX, 2) + FMath::Pow(SubstractInY, 2));
			if (Iterator->GetClass()->IsChildOf(AEnemy::StaticClass()) &&
				Distance < MinimumDistance)
			{
				LockedEnemy = Cast<AEnemy>(*Iterator);
				MinimumDistance = Distance;
			}
		}
	}

	// Move Projectile towards the nearest enemy
	if (LockedEnemy != nullptr)
	{
		FVector Direction = LockedEnemy->GetActorLocation() - StaticMesh->GetComponentLocation();
		FVector NewLocation = StaticMesh->GetComponentLocation() - (Direction * -1 * GetSpeed() * 100 * DeltaTime);
		StaticMesh->SetWorldLocation(NewLocation);
	}
}
	
