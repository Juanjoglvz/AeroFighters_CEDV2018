// Fill out your copyright notice in the Description page of Project Settings.

#include "ShootStraightBehaviour.h"
#include "EnemyLaser.h"
#include "Engine.h"

UShootStraightBehaviour::UShootStraightBehaviour()
{}

void UShootStraightBehaviour::Shoot(UWorld* World, FVector Location, FRotator Rotation)
{
	FActorSpawnParameters SpawnInfo;
	World->SpawnActor <AEnemyLaser>(Location, Rotation, SpawnInfo); 
}

