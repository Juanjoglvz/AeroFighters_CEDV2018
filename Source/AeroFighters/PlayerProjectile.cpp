/* Copyright (C) 2018 Iván García, Juan José Corroto and Javier Córdoba - All Rights Reserved
* You may use, distribute and modify this code under the
* terms of the GNU GPLv3 license.
*
* You should have received a copy of the GNU GPLv3 license with
* this file. If not, please write to: ivan.garcia16@alu.uclm.es
*/

#include "PlayerProjectile.h"


// Sets default values
APlayerProjectile::APlayerProjectile() : Super()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check if the projectile has to be destroyed
	if (StaticMesh->GetComponentLocation().X > TopMovableArea->GetActorLocation().X + 100.f)
	{
		this->Destroy();
	}

	// The basic movement (go up) is the same for all player projectile types
	FVector NewLocation = StaticMesh->GetComponentLocation() + (FVector{ 1.f, 0.f, 0.f } * GetSpeed() * DeltaTime);
	NewLocation.Z = 200.f;
	StaticMesh->SetWorldLocation(NewLocation);
	//StaticMesh->SetWorldRotation(FRotator(90.f, 0.f, 0.f));
}

