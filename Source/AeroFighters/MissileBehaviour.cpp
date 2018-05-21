/* Copyright (C) 2018 Iván García, Juan José Corroto and Javier Córdoba - All Rights Reserved
* You may use, distribute and modify this code under the
* terms of the GNU GPLv3 license.
*
* You should have received a copy of the GNU GPLv3 license with
* this file. If not, please write to: ivan.garcia16@alu.uclm.es
*/

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


