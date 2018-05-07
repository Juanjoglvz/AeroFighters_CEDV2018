// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerProjectile.h"
#include "PlayerLaser.generated.h"

UCLASS()
class AEROFIGHTERS_API APlayerLaser : public APlayerProjectile
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlayerLaser();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void ProjectileBehaviour(float DeltaTime) override;
};