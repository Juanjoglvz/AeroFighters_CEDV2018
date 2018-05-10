// Fill out your copyright notice in the Description page of Project Settings.

#include "ShootStraightBehaviour.h"
#include "EnemyLaser.h"
#include "Engine.h"

UShootStraightBehaviour::UShootStraightBehaviour()
{

}

void UShootStraightBehaviour::Shoot(FVector Location, FRotator Rotation, float DeltaTime)
{
	FActorSpawnParameters SpawnInfo;
	this->World->SpawnActor <AEnemyLaser>(Location, Rotation, SpawnInfo); 
}

