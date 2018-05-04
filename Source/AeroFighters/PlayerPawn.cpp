// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	//Set Skeletal Mesh
	auto SkeletalMeshAsset = ConstructorHelpers::FObjectFinder<USkeletalMesh>(TEXT("SkeletalMesh'/Game/Assets/Ships/SimpleSpaceship'"));

	if (SkeletalMeshAsset.Succeeded()) {
		SkeletalMeshComponent->SetSkeletalMesh(SkeletalMeshAsset.Object);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(2, 15.f, FColor::Red, TEXT("Ship Mesh didn't load correctly"));
	}

	//Take control of player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Add OnHit function to OnActorHit event
	OnActorHit.AddDynamic(this, &APlayerPawn::OnHit);

}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Move at the same rate as the camera
	FVector NewLocation = GetActorLocation();

	NewLocation += GetActorForwardVector() * CameraSpeed * DeltaTime;

	//Handle movement based on our "MoveX" and "MoveY" axes
	if (!MovementInput.IsZero())
	{
		//Scale our movement input axis values by 100 units per second
		MovementInput = MovementInput.GetSafeNormal() * MoveSpeed;
		NewLocation += GetActorForwardVector() * MovementInput.X * DeltaTime;
		NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime;
	}
	SetActorLocation(NewLocation);
	

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Bind Input functions
	InputComponent->BindAxis("MoveForward", this, &APlayerPawn::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerPawn::MoveRight);

}

void APlayerPawn::MoveForward(float AxisValue) 
{
	MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void APlayerPawn::MoveRight(float AxisValue)
{
	MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void APlayerPawn::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		if (OtherActor->GetClass()->IsChildOf(AEnemyProjectile::StaticClass()))
		{
			OtherActor->Destroy();
			SelfActor->Destroy();
		}
	}
}