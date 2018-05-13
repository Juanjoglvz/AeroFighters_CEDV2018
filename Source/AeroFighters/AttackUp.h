// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Powerup.h"
#include "AttackUp.generated.h"

/**
 * 
 */
UCLASS()
class AEROFIGHTERS_API AAttackUp : public APowerup
{
	GENERATED_BODY()
	
public:
	AAttackUp();
	virtual void Tick(float DeltaTime) override;

	virtual void CollisionAction(APlayerCharacter * Character) override;
	
};
