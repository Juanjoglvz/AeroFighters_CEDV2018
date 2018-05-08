// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"

// Sets default values
AEnemy::AEnemy() : CameraSpeed{ 150.f, 0.f, 0.f }
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Move at the same rate as the camera
	FVector NewLocation = GetActorLocation();

	NewLocation += CameraSpeed * DeltaTime;
	SetActorLocation(NewLocation);
}

void AEnemy::SetStaticMesh(UStaticMesh* Mesh)
{
	StaticMeshComponent->SetStaticMesh(Mesh);
	StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}
