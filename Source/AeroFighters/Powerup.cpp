// Fill out your copyright notice in the Description page of Project Settings.

#include "Powerup.h"


// Sets default values
APowerup::APowerup() : MoveSpeed(0.2f), CameraSpeed{ 150.f, 0.f, 0.f }
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	auto BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));

	BoxCollision->SetCollisionProfileName(TEXT("OverlapAll"));
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->bGenerateOverlapEvents = true;

	Direction = FVector(RandomFloat(-100, 100), RandomFloat(-100, 100), 0.0f);
}

void APowerup::SetStaticMeshAsset(UStaticMesh* StaticMeshAsset)
{
	StaticMeshComponent->SetStaticMesh(StaticMeshAsset);
	StaticMeshComponent->SetMobility(EComponentMobility::Movable);
	StaticMeshComponent->SetEnableGravity(false);
	StaticMeshComponent->SetSimulatePhysics(false);
	StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void APowerup::SetUp(float MoveSpeed, UWorld* World)
{
	this->MoveSpeed = MoveSpeed;

	//Get The references to the borders
	FString TopMovableAreaString = FString(TEXT("TopMovableArea"));
	FString BottomMovableAreaString = FString(TEXT("BottomMovableArea"));
	FString RightMovableAreaString = FString(TEXT("RightMovableArea"));
	FString LeftMovableAreaString = FString(TEXT("LeftMovableArea"));
	uint32 i = 0;
	for (TActorIterator<AActor> itr(World); itr; ++itr)
	{
		if (TopMovableAreaString.Equals(itr->GetName()))
		{
			this->TopMovableArea = *itr;
			i++;
		}
		else if (BottomMovableAreaString.Equals(itr->GetName()))
		{
			this->BottomMovableArea = *itr;
			i++;
		}
		else if (RightMovableAreaString.Equals(itr->GetName()))
		{
			this->RightMovableArea = *itr;
			i++;
		}
		else if (LeftMovableAreaString.Equals(itr->GetName()))
		{
			this->LeftMovableArea = *itr;
			i++;
		}

		if (i > 3)
		{
			break;
		}
	}
}

// Called when the game starts or when spawned
void APowerup::BeginPlay()
{
	Super::BeginPlay();
	
}

void APowerup::OnOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	GEngine->AddOnScreenDebugMessage(2, 15.f, FColor::Red, TEXT("Holi"));
	if (OtherActor)
	{
		if (OtherActor->GetClass()->IsChildOf(APowerup::StaticClass()))
		{
		}
	}
}

// Called every frame
void APowerup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move(DeltaTime);

}

void APowerup::Move(float DeltaTime)
{
	FVector NewLocation = GetActorLocation();

	NewLocation += CameraSpeed * DeltaTime;

	NewLocation += Direction * MoveSpeed * DeltaTime;

	SetActorLocation(NewLocation);

	UE_LOG(LogTemp, Display, TEXT("X:%f  Y:%f  Z:%f"), Direction.X, Direction.Y, Direction.Z);
}

float APowerup::RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}