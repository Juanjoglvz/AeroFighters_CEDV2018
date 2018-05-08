// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.h"
#include "EnemyProjectile.generated.h"

UCLASS(Abstract)
class AEROFIGHTERS_API AEnemyProjectile : public AProjectile
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void OnBomb();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;	
};
