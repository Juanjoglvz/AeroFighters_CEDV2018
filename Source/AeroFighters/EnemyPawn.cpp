// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyPawn.h"
#include "Engine.h"

// Sets default values
AEnemyPawn::AEnemyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("EnemyRootComponent"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
}

// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemyPawn::SetStaticMeshAsset(UStaticMesh* StaticMeshAsset)
{
	StaticMeshComponent->SetStaticMesh(StaticMeshAsset);
	StaticMeshComponent->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

