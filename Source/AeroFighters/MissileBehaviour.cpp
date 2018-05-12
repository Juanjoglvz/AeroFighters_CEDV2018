// Fill out your copyright notice in the Description page of Project Settings.

#include "MissileBehaviour.h"
#include "EnemyMissile.h"
#include "Engine.h"

UMissileBehaviour::UMissileBehaviour()
{
	this->Timer = 0.f;
	this->ShootTimer = 4.f;
}

void UMissileBehaviour::Shoot(UWorld* World, FVector Location, FRotator Rotation, float DeltaTime)
{
	Timer += DeltaTime;
	if (Timer > ShootTimer)
	{
		FActorSpawnParameters SpawnInfo;
		World->SpawnActor <AEnemyMissile>(Location, Rotation, SpawnInfo);

		Timer = 0.f;
	}
}


