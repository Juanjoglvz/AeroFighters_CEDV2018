/* Copyright (C) 2018 Iván García, Juan José Corroto and Javier Córdoba - All Rights Reserved
* You may use, distribute and modify this code under the
* terms of the GNU GPLv3 license.
*
* You should have received a copy of the GNU GPLv3 license with
* this file. If not, please write to: ivan.garcia16@alu.uclm.es
*/

#include "Asteroid.h"


// Sets default values
AAsteroid::AAsteroid() : RotationDrift(FRotator(0.0f, 0.0f, 0.0f)), RotationDriftSpeed(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;    
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	//Set Skeletal Mesh
	auto StaticMeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Assets/Asteroid/Asteroid.Asteroid'"));

	if (StaticMeshAsset.Succeeded()) {
		StaticMeshComponent->SetStaticMesh(StaticMeshAsset.Object);
		StaticMeshComponent->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
		StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
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
	FRotator RotationIncrease = RotationDrift * RotationDriftSpeed * DeltaTime;

	AddActorWorldRotation(RotationIncrease);
}


void AAsteroid::SetRotationDrift(FRotator RDrift)
{
	RotationDrift = RDrift;
}

void AAsteroid::SetRotationDriftSpeed(float speed)
{
	RotationDriftSpeed = speed;
}
