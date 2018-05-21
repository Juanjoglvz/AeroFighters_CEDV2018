/* Copyright (C) 2018 Iv�n Garc�a, Juan Jos� Corroto and Javier C�rdoba - All Rights Reserved
* You may use, distribute and modify this code under the
* terms of the GNU GPLv3 license.
*
* You should have received a copy of the GNU GPLv3 license with
* this file. If not, please write to: ivan.garcia16@alu.uclm.es
*/

#include "AttackUp.h"


AAttackUp::AAttackUp() : Super()
{
	PrimaryActorTick.bCanEverTick = true;

	auto StaticMeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Assets/Powerup/electricity.electricity'"));

	if (StaticMeshAsset.Succeeded())
	{
		SetStaticMeshAsset(StaticMeshAsset.Object);
	}
}

void AAttackUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAttackUp::CollisionAction(APlayerCharacter* Character)
{
	if (Character)
	{
		Character->IncreasePower();
	}
}
