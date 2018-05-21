/* Copyright (C) 2018 Iván García, Juan José Corroto and Javier Córdoba - All Rights Reserved
* You may use, distribute and modify this code under the
* terms of the GNU GPLv3 license.
*
* You should have received a copy of the GNU GPLv3 license with
* this file. If not, please write to: ivan.garcia16@alu.uclm.es
*/

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

	SetSpeed(150.f);
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
	FVector NewLocation = StaticMesh->GetComponentLocation();
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

			//When not locked on enemy and searching for one, move straight
			NewLocation.X += 1.5f * DeltaTime;
		}
	}

	// Move Projectile towards the nearest enemy
	else if (LockedEnemy != nullptr)
	{
		FVector Direction = LockedEnemy->GetActorLocation() - StaticMesh->GetComponentLocation();
		// Rotate towards the enemy
		FRotator EnemyRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
		StaticMesh->SetRelativeRotation(EnemyRotation, false, nullptr, ETeleportType::TeleportPhysics);

		// The projectile moves towards the enemy
		Direction.Normalize(); // Normalize the vector so it doesnt slow down when near the player
		NewLocation += (Direction * GetSpeed() * DeltaTime * 1.5f);
		
	}
	NewLocation.Z = 200.f;
	StaticMesh->SetWorldLocation(NewLocation);
}
	
