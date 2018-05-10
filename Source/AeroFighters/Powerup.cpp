// Fill out your copyright notice in the Description page of Project Settings.

#include "Powerup.h"


// Sets default values
APowerup::APowerup() : MoveSpeed(0.0f), CameraSpeed{ 150.f, 0.f, 0.f }
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	//Set Skeletal Mesh
	auto StaticMeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Assets/Projectile/Projectile.Projectile'"));
	if (StaticMeshAsset.Succeeded())
		SetStaticMeshAsset(StaticMeshAsset.Object);
	else
		GEngine->AddOnScreenDebugMessage(2, 15.f, FColor::Red, TEXT("Pero bueno folagor"));
}

void APowerup::SetStaticMeshAsset(UStaticMesh* StaticMeshAsset)
{
	StaticMesh->SetStaticMesh(StaticMeshAsset);
	StaticMesh->SetMobility(EComponentMobility::Movable);
	StaticMesh->SetEnableGravity(false);
	StaticMesh->SetSimulatePhysics(false);
	StaticMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
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

// Called every frame
void APowerup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APowerup::Move(float DeltaTime)
{
}

