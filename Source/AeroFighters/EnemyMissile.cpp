// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyMissile.h"
#include "PlayerLaser.h"
#include "PlayerCharacter.h"
#include "Engine.h"

// Sets default values
AEnemyMissile::AEnemyMissile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Get StaticMesh associated with this projectile 
	auto StaticMeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Assets/Projectile/BasicMissile.BasicMissile'"));

	if (StaticMeshAsset.Succeeded())
		SetStaticMeshAsset(StaticMeshAsset.Object);
	
	SetSpeed(50.f);
}

// Called when the game starts or when spawned
void AEnemyMissile::BeginPlay()
{
	Super::BeginPlay();
	
	// Get a reference to the character
	CharacterReference = GetWorld()->GetFirstPlayerController()->GetCharacter();

	// Scale the StaticMesh
	StaticMesh->SetWorldScale3D(FVector(7.f, 7.f, 7.f));
	StaticMesh->SetRelativeScale3D(FVector(7.f, 7.f, 7.f));
}

void AEnemyMissile::ProjectileBehaviour(float DeltaTime)
{
	// Get the movement direction
	if (CharacterReference.Get() != nullptr)
	{
		FVector Direction = CharacterReference->GetActorLocation() - StaticMesh->GetComponentLocation();

		// Rotate towards the player
		FRotator EnemyRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
		StaticMesh->SetRelativeRotation(EnemyRotation, false, nullptr, ETeleportType::TeleportPhysics);

		Direction.Normalize(); // Normalize the vector so it doesnt slow down when near the player
		// The projectile moves towards player
		FVector NewLocation = StaticMesh->GetComponentLocation() + (Direction * GetSpeed() * DeltaTime * 1.5f);
		NewLocation.Z = 200.f;

		//Camera Stuff 
		NewLocation.X += 150.f * DeltaTime;


		StaticMesh->SetWorldLocation(NewLocation);
	}
}


void AEnemyMissile::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	
	if (OtherActor)
	{
		if (OtherActor->GetClass()->IsChildOf(APlayerLaser::StaticClass()))
		{
			this->Destroy();
		}
		else if (OtherActor->GetClass()->IsChildOf(APlayerCharacter::StaticClass()))
		{
			/* The missile is destroyed because if we destroy the missile here 
			the player does not get the collision notification and cannot decrease its life
			this->Destroy();
			*/
		}
	}
}