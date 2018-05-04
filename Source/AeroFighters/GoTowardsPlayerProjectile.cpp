// Fill out your copyright notice in the Description page of Project Settings.

#include "GoTowardsPlayerProjectile.h"
#include "Engine.h"

// Sets default values
AGoTowardsPlayerProjectile::AGoTowardsPlayerProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Get StaticMesh associated with this projectile 
	auto StaticMeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Assets/Projectile/TowardsPlayer.TowardsPlayer'"));

	if (StaticMeshAsset.Succeeded())
		SetStaticMeshAsset(StaticMeshAsset.Object);

	SetSpeed(5.f);
}

// Called when the game starts or when spawned
void AGoTowardsPlayerProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	// Get a reference to the pawn
	PawnReference = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void AGoTowardsPlayerProjectile::Clone()
{
}

void AGoTowardsPlayerProjectile::ProjectileBehaviour(float DeltaTime)
{
	// The projectile moves towards player
	FVector Direction = PawnReference->GetActorLocation() - StaticMesh->GetComponentLocation();
	FVector NewLocation = StaticMesh->GetComponentLocation() + (Direction * GetSpeed() * DeltaTime);
	StaticMesh->SetWorldLocation(NewLocation);
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, FString::Printf(TEXT("%f,%f,%f"), NewLocation.X, NewLocation.Y, NewLocation.Z));
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("%f,%f,%f"), PawnReference->GetActorLocation().X, PawnReference->GetActorLocation().Y, PawnReference->GetActorLocation().Z));
}

