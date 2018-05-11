// Fill out your copyright notice in the Description page of Project Settings.

#include "MissileBehaviour.h"
#include "EnemyMissile.h"
#include "Engine.h"

UMissileBehaviour::UMissileBehaviour()
{
}

void UMissileBehaviour::Shoot(FVector Location, FRotator Rotation, float DeltaTime)
{
	FActorSpawnParameters SpawnInfo;
	World->SpawnActor <AEnemyMissile>(Location, Rotation, SpawnInfo);
}


