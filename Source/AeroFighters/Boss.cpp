// Fill out your copyright notice in the Description page of Project Settings.

#include "Boss.h"
#include "PlayerProjectile.h"
#include "PlayerLaser.h"
#include "PlayerMissile.h"


// Sets default values
ABoss::ABoss() : CameraSpeed {150.0f, 0.0f, 0.0f}, Hp{100}, LaserDmg{10}, MissileDmg{50}
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	auto BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));

	BoxCollision->SetCollisionProfileName(TEXT("OverlapAll"));
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->bGenerateOverlapEvents = true;
	StaticMeshComponent->SetupAttachment(RootComponent);

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ABoss::OnOverlap);

	auto StaticMeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Assets/Ships/Frigate'"));

	if (StaticMeshAsset.Succeeded())
	{
		StaticMeshComponent->SetStaticMesh(StaticMeshAsset.Object);
		StaticMeshComponent->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
		StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	}

}

// Called when the game starts or when spawned
void ABoss::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	NewLocation += CameraSpeed * DeltaTime;

	if (IsValid(Position))
	{
		if (this->GetActorLocation().X > (this->Position->GetActorLocation().X + 550))
		{
			NewLocation.X -= 50 * DeltaTime;
		}
	}


	SetActorLocation(NewLocation);

}

// Called to bind functionality to input
void ABoss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABoss::SetPosition(AActor* Position)
{
	this->Position = Position;
}


void ABoss::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		if (OtherActor->GetClass()->IsChildOf(APlayerProjectile::StaticClass()))
		{
			// Reduce health and destroy if less than 0
			if (OtherActor->GetClass()->IsChildOf(APlayerLaser::StaticClass()))
			{
				this->Hp -= this->LaserDmg;
			}
			else if (OtherActor->GetClass()->IsChildOf(APlayerMissile::StaticClass()))
			{
				this->Hp -= this->MissileDmg;
			}
			if (this->Hp < 0)
			{
				this->Destroy();
			}


			OtherActor->Destroy();
		}
	}
}
