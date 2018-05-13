// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Powerup.h"
#include "BombUp.generated.h"

/**
 * 
 */
UCLASS()
class AEROFIGHTERS_API ABombUp : public APowerup
{
	GENERATED_BODY()

public:
	ABombUp();
	virtual void Tick(float DeltaTime) override;

	virtual void CollisionAction(APlayerCharacter * Character) override;
};
