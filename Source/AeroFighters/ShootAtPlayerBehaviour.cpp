// Fill out your copyright notice in the Description page of Project Settings.

#include "ShootAtPlayerBehaviour.h"
#include "EnemyLaser.h"
#include "Engine.h"

UShootAtPlayerBehaviour::UShootAtPlayerBehaviour() 
{}

void UShootAtPlayerBehaviour::Shoot(FVector Location, FRotator Rotation, float DeltaTime)
{
	FActorSpawnParameters SpawnInfo;
	AEnemyLaser* EnemyLaser = World->SpawnActor <AEnemyLaser>(Location, Rotation, SpawnInfo);
	FVector Direction = UGameplayStatics::GetPlayerCharacter(World, 0)->GetActorLocation();
	EnemyLaser->SetDirection(Direction);
}



