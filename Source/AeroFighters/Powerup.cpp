// Fill out your copyright notice in the Description page of Project Settings.

#include "Powerup.h"
#include "PlayerCharacter.h"

// Sets default values
APowerup::APowerup() : MoveSpeed(3.0f), CameraSpeed{ 150.f, 0.f, 0.f }, LastCollidedArea(nullptr)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	auto BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));

	BoxCollision->SetCollisionProfileName(TEXT("OverlapAll"));
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->bGenerateOverlapEvents = true;
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &APowerup::OnOverlap);

	Direction = FVector(RandomFloat(-100, 100), RandomFloat(-100, 100), 0.0f);
}

void APowerup::SetStaticMeshAsset(UStaticMesh* StaticMeshAsset)
{
	StaticMeshComponent->SetStaticMesh(StaticMeshAsset);
	StaticMeshComponent->SetMobility(EComponentMobility::Movable);
	StaticMeshComponent->SetEnableGravity(false);
	StaticMeshComponent->SetSimulatePhysics(false);
	StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
}

void APowerup::SetSpeed(float MoveSpeed)
{
	this->MoveSpeed = MoveSpeed;
}

void APowerup::SetUp(UWorld * World)
{
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
	
	SetUp(GetWorld());
}

void APowerup::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{		
		if (OtherActor->GetClass()->IsChildOf(APlayerCharacter::StaticClass()))
		{
			APlayerCharacter* Character = (APlayerCharacter*)OtherActor;
			GEngine->AddOnScreenDebugMessage(2, 2.f, FColor::Red, TEXT("Collided with player"));
			// Do some stuff with Powerups
			CollisionAction(Character);
			this->Destroy();
		}
	}
}

// Called every frame
void APowerup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ChangeDirection(GetActorLocation());

	Move(DeltaTime);

}

void APowerup::ChangeDirection(FVector Position)
{
	if (Position.X < BottomMovableArea.Get()->GetActorLocation().X && LastCollidedArea.Get() != BottomMovableArea.Get())
	{
		Direction.X *= -1;
		LastCollidedArea = BottomMovableArea;
	}
	else if (Position.X > TopMovableArea.Get()->GetActorLocation().X && LastCollidedArea.Get() != TopMovableArea.Get())
	{
		Direction.X *= -1;
		LastCollidedArea = TopMovableArea;
	}
	else if (Position.Y > RightMovableArea.Get()->GetActorLocation().Y && LastCollidedArea.Get() != RightMovableArea.Get())
	{
		Direction.Y *= -1;
		LastCollidedArea = RightMovableArea;
	}
	else if (Position.Y < LeftMovableArea.Get()->GetActorLocation().Y && LastCollidedArea.Get() != LeftMovableArea.Get())
	{
		Direction.Y *= -1;
		LastCollidedArea = LeftMovableArea;
	}
}

void APowerup::Move(float DeltaTime)
{
	FVector NewLocation = GetActorLocation();

	NewLocation += CameraSpeed * DeltaTime;

	NewLocation += Direction * MoveSpeed * DeltaTime;

	SetActorLocation(NewLocation);
}

float APowerup::RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}