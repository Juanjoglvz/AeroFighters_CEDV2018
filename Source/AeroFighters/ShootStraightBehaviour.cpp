/* Copyright (C) 2018 Iván García, Juan José Corroto and Javier Córdoba - All Rights Reserved
* You may use, distribute and modify this code under the
* terms of the GNU GPLv3 license.
*
* You should have received a copy of the GNU GPLv3 license with
* this file. If not, please write to: ivan.garcia16@alu.uclm.es
*/

#include "ShootStraightBehaviour.h"
#include "EnemyLaser.h"
#include "Engine.h"

UShootStraightBehaviour::UShootStraightBehaviour()
{
	this->ShootTimer = 2.2f;
	this->Timer = (((float)rand() / (float)RAND_MAX)) * ShootTimer;
}

void UShootStraightBehaviour::Shoot(UWorld* World, FVector Location, FRotator Rotation, float DeltaTime)
{
	Timer += DeltaTime;
	if (Timer > ShootTimer)
	{
		FActorSpawnParameters SpawnInfo;
		World->SpawnActor <AEnemyLaser>(Location, Rotation, SpawnInfo);
		Timer = 0.f;
	}
}

