/* Copyright (C) 2018 Iván García, Juan José Corroto and Javier Córdoba - All Rights Reserved
* You may use, distribute and modify this code under the
* terms of the GNU GPLv3 license.
*
* You should have received a copy of the GNU GPLv3 license with
* this file. If not, please write to: ivan.garcia16@alu.uclm.es
*/

#include "EnemyAsteroid.h"


AEnemyAsteroid::AEnemyAsteroid() : Super()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	auto StaticMeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Assets/Asteroid/Asteroid1.Asteroid1'"));

	if (StaticMeshAsset.Succeeded())
		StaticMeshComponent->SetStaticMesh(StaticMeshAsset.Object);
}

AAsteroid* AEnemyAsteroid::clone()
{
	return GetWorld()->SpawnActor<AAsteroid>(AEnemyAsteroid::StaticClass(), StaticMeshComponent->GetComponentTransform());
}