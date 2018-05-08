// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyMissile.h"
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
	
	SetSpeed(200.f);
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

		// The projectile moves towards player
		FVector NewLocation = StaticMesh->GetComponentLocation() + (Direction * GetSpeed() * DeltaTime * 0.0001f);
		NewLocation.Z = 200.f;
		StaticMesh->SetWorldLocation(NewLocation);
	}
}

