/* Copyright (C) 2018 Iván García, Juan José Corroto and Javier Córdoba - All Rights Reserved
* You may use, distribute and modify this code under the
* terms of the GNU GPLv3 license.
*
* You should have received a copy of the GNU GPLv3 license with
* this file. If not, please write to: ivan.garcia16@alu.uclm.es
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyProjectile.h"
#include "EnemyLaser.generated.h"

UCLASS()
class AEROFIGHTERS_API AEnemyLaser : public AEnemyProjectile
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyLaser();

	void SetDirection(FVector Direction_);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void ProjectileBehaviour(float DeltaTime) override;

private:
	FVector Direction;
};
