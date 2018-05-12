// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include "PlayerProjectile.h"

// Sets default values
AEnemy::AEnemy() : CameraSpeed{ 150.f, 0.f, 0.f }
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

void AEnemy::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		if (OtherActor->GetClass()->IsChildOf(APlayerProjectile::StaticClass()))
		{
			this->Destroy();
			OtherActor->Destroy();
		}
	}
}