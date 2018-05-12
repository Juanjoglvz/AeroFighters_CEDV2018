// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Asteroid.h"
#include "EnemyAsteroid.generated.h"

/**
 * 
 */
UCLASS()
class AEROFIGHTERS_API AEnemyAsteroid : public AAsteroid
{
	GENERATED_BODY()
	
public:
	AEnemyAsteroid();

	virtual AAsteroid* clone();
	
};
