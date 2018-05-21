/* Copyright (C) 2018 Iván García, Juan José Corroto and Javier Córdoba - All Rights Reserved
* You may use, distribute and modify this code under the
* terms of the GNU GPLv3 license.
*
* You should have received a copy of the GNU GPLv3 license with
* this file. If not, please write to: ivan.garcia16@alu.uclm.es
*/

#include "BombUp.h"


ABombUp::ABombUp() : Super()
{
	PrimaryActorTick.bCanEverTick = true;

	auto StaticMeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Assets/Powerup/bomb.bomb'"));

	if (StaticMeshAsset.Succeeded())
	{
		SetStaticMeshAsset(StaticMeshAsset.Object);
	}
}

void ABombUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABombUp::CollisionAction(APlayerCharacter* Character)
{
	if (Character)
	{
		Character->IncreaseBombs();
	}
}
