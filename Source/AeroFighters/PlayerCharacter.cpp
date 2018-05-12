// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "PlayerLaser.h"
#include "EnemyProjectile.h"
#include "PlayerMissile.h"
#include "Engine.h"


// Sets default values
APlayerCharacter::APlayerCharacter() : NumberOfBombsAvailable{ 3 }, NumberOfLives{ 5 }, MoveSpeed { 1000.f }, CameraSpeed{ 150.f, 0.f, 0.f }, 
b_IsShooting{ false }, Timer{ 0.25f }, ShootTimer{ 0.25f }, CurrentPower{ PlayerPower::WideShot}
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	//Set Static Mesh
	auto StaticMeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Assets/Ships/Plane'"));

	if (StaticMeshAsset.Succeeded()) {
		StaticMeshComponent->SetStaticMesh(StaticMeshAsset.Object);
		StaticMeshComponent->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
		StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(2, 15.f, FColor::Red, TEXT("Ship Mesh didn't load correctly"));
	}

	//Take control of player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Add OnHit function to OnActorHit event
	GetCapsuleComponent()->bGenerateOverlapEvents = true;
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("OverlapAll"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Get The references to the borders
	FString TopMovableAreaString = FString(TEXT("TopMovableArea"));
	FString BottomMovableAreaString = FString(TEXT("BottomMovableArea"));
	FString RightMovableAreaString = FString(TEXT("RightMovableArea"));
	FString LeftMovableAreaString = FString(TEXT("LeftMovableArea"));
	uint32 i = 0;
	for (TActorIterator<AActor> itr(GetWorld()); itr; ++itr)
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

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Move at the same rate as the camera
	FVector NewLocation = GetActorLocation();

	NewLocation += CameraSpeed * DeltaTime;
	FVector NewMovedLocationX = FVector(NewLocation.X, NewLocation.Y, NewLocation.Z);
	FVector NewMovedLocationY = FVector(NewLocation.X, NewLocation.Y, NewLocation.Z);

	//Handle movement based on our "MoveX" and "MoveY" axes
	if (!MovementInput.IsZero())
	{
		//Scale our movement input axis values by 1000 units per second
		MovementInput = MovementInput.GetSafeNormal() * MoveSpeed;
		NewMovedLocationX += GetActorForwardVector() * MovementInput.X * DeltaTime;
		if (IsPosMoveX(NewMovedLocationX))
		{
			NewLocation.X = NewMovedLocationX.X;
		}
		NewMovedLocationY += GetActorRightVector() * MovementInput.Y * DeltaTime;
		if (IsPosMoveY(NewMovedLocationY))
		{
			NewLocation.Y = NewMovedLocationY.Y;
		}
	}

	SetActorLocation(NewLocation);

	Shoot(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Bind Input functions
	InputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	InputComponent->BindAction("Bomb", IE_Pressed, this, &APlayerCharacter::ThrowABomb);
	InputComponent->BindAction("NormalShoot", IE_Pressed, this, &APlayerCharacter::Shoot);
	InputComponent->BindAction("NormalShoot", IE_Released, this, &APlayerCharacter::StopShooting);
}

void APlayerCharacter::MoveForward(float AxisValue)
{
	MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void APlayerCharacter::MoveRight(float AxisValue)
{
	MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

// If character throw a bomb, all enemy projectiles will be destroyed
void APlayerCharacter::ThrowABomb()
{
	if (NumberOfBombsAvailable > 0)
	{
		myDiscardEnemyShootsDelegate.Broadcast();
		NumberOfBombsAvailable--;
	}
}

void APlayerCharacter::Shoot()
{
	b_IsShooting = true;
}

void APlayerCharacter::StopShooting()
{
	b_IsShooting = false;
}

bool APlayerCharacter::IsPosMoveX(FVector NewPos) const
{
	//Check if possible to move in X axis
	if (NewPos.X >= this->BottomMovableArea->GetActorLocation().X && NewPos.X <= this->TopMovableArea->GetActorLocation().X)
	{
		return true;
	}

	return false;
}

bool APlayerCharacter::IsPosMoveY(FVector NewPos) const
{
	//Check if possible to move in Y axis
	if (NewPos.Y >= this->LeftMovableArea->GetActorLocation().Y && NewPos.Y <= this->RightMovableArea->GetActorLocation().Y)
	{
		return true;
	}

	return false;
}

void APlayerCharacter::Shoot(float DeltaTime)
{
	// Check if player is shooting. If player is shooting, spawns projectiles.
	Timer += DeltaTime;
	if (b_IsShooting && Timer > ShootTimer)
	{
		FRotator Rotation(0.f, 0.f, 0.f);
		FActorSpawnParameters SpawnInfo;
		if (CurrentPower == PlayerPower::BasicShot)
		{
			for (int i = -1; i <= 1; i++)
			{
				FVector Location = this->GetActorLocation();
				Location += FVector(10.f, i * 20.f, 0.f);
				if (i == 0)
				{
					Location += FVector(20.f, 0.f, 0.f);
				}
				GetWorld()->SpawnActor <APlayerLaser>(Location, Rotation, SpawnInfo);
			}
		}
		else if (CurrentPower == PlayerPower::WideShot)
		{
			for (int i = -2; i <= 2; i++)
			{
				FVector Location = this->GetActorLocation();
				Location += FVector(10.f, i * 30.f, 0.f);
				if (i == 0)
				{
					Location += FVector(20.f, 0.f, 0.f);
				}
				GetWorld()->SpawnActor <APlayerLaser>(Location, Rotation, SpawnInfo);
			}
		}
		Timer = 0.f;
	}
}

void APlayerCharacter::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor)
{
	if (OtherActor)
	{
		if (OtherActor->GetClass()->IsChildOf(AEnemyProjectile::StaticClass()))
		{
			if (NumberOfLives > 0)
			{
				GEngine->AddOnScreenDebugMessage(3, 5.f, FColor::Red, FString(TEXT("Me han dao!")) + FString::FromInt(this->NumberOfLives));
				NumberOfLives--;
				//Make player invulnerable
			}
			else {
				OtherActor->Destroy();
				this->Destroy();
				UGameplayStatics::SetGamePaused(this, true);
			}
		}
	}
}