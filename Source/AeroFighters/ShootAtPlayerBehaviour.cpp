// Fill out your copyright notice in the Description page of Project Settings.

#include "ShootAtPlayerBehaviour.h"
#include "EnemyLaser.h"
#include "Engine.h"

UShootAtPlayerBehaviour::UShootAtPlayerBehaviour() 
{
	this->Timer = 0.f;
	this->ShootTimer = 2.f;
}

void UShootAtPlayerBehaviour::Shoot(UWorld* World, FVector Location, FRotator Rotation, float DeltaTime)
{
	Timer += DeltaTime;
	if (Timer > ShootTimer)
	{
		FActorSpawnParameters SpawnInfo;
		AEnemyLaser* EnemyLaser = World->SpawnActor <AEnemyLaser>(Location, Rotation, SpawnInfo);
		FVector Direction = UGameplayStatics::GetPlayerCharacter(World, 0)->GetActorLocation() - EnemyLaser->GetStaticMesh()->GetComponentLocation();
		EnemyLaser->SetDirection(Direction);

		Timer = 0.f;
	}
}



