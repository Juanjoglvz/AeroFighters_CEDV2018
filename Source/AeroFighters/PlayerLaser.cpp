/* Copyright (C) 2018 Iván García, Juan José Corroto and Javier Córdoba - All Rights Reserved
* You may use, distribute and modify this code under the
* terms of the GNU GPLv3 license.
*
* You should have received a copy of the GNU GPLv3 license with
* this file. If not, please write to: ivan.garcia16@alu.uclm.es
*/

#include "PlayerLaser.h"
#include "Engine.h"


// Sets default values
APlayerLaser::APlayerLaser() : Super()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Get StaticMesh associated with this projectile 
	auto StaticMeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Assets/Projectile/BasicShot.BasicShot'"));

	if (StaticMeshAsset.Succeeded())
		SetStaticMeshAsset(StaticMeshAsset.Object);

	SetSpeed(1000.f);
}

// Called when the game starts or when spawned
void APlayerLaser::BeginPlay()
{
	Super::BeginPlay();
	StaticMesh->SetWorldScale3D(FVector(5.f, 5.f, 2.f));
	StaticMesh->SetRelativeScale3D(FVector(5.f, 5.f, 2.f));
	StaticMesh->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f), false, nullptr, ETeleportType::TeleportPhysics);
}

void APlayerLaser::ProjectileBehaviour(float DeltaTime)
{
}
