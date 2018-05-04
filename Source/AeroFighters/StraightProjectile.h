// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyProjectile.h"
#include "StraightProjectile.generated.h"

UCLASS()
class AEROFIGHTERS_API AStraightProjectile : public AEnemyProjectile
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStraightProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Clone() override;
	virtual void ProjectileBehaviour(float DeltaTime) override;

};
