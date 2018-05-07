// Fill out your copyright notice in the Description page of Project Settings.

#include "Asteroid.h"


// Sets default values
AAsteroid::AAsteroid() : RotationDrift(FRotator(0.0f, 0.0f, 0.0f)), RotationDriftSpeed(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;    
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	//Set Skeletal Mesh
	auto StaticMeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Assets/Projectile/Projectile.Projectile'"));

	if (StaticMeshAsset.Succeeded()) {
		StaticMeshComponent->SetStaticMesh(StaticMeshAsset.Object);
		StaticMeshComponent->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
		StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(2, 15.f, FColor::Red, TEXT("Ship Mesh didn't load correctly"));
	}
}

AAsteroid* AAsteroid::clone()
{	
	return GetWorld()->SpawnActor<AAsteroid>(AAsteroid::StaticClass(), StaticMeshComponent->GetComponentTransform());
}

// Called when the game starts or when spawned
void AAsteroid::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator OriginalRotation = GetActorRotation();
	FRotator NewRotation = OriginalRotation + RotationDrift * RotationDriftSpeed * DeltaTime;
	
	SetActorRotation(NewRotation);
}


void AAsteroid::SetRotationDrift(FRotator RDrift)
{
	RotationDrift = RDrift;
}

void AAsteroid::SetRotationDriftSpeed(float speed)
{
	RotationDriftSpeed = speed;
}
