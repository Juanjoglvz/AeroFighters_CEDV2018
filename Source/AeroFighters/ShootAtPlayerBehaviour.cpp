/* Copyright (C) 2018 Iván García, Juan José Corroto and Javier Córdoba - All Rights Reserved
* You may use, distribute and modify this code under the
* terms of the GNU GPLv3 license.
*
* You should have received a copy of the GNU GPLv3 license with
* this file. If not, please write to: ivan.garcia16@alu.uclm.es
*/

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
		EnemyLaser->SetDirection(Direction.GetSafeNormal());

		Timer = 0.f;
	}
}



