// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyPawn.h"
#include "BasicEnemyPawn.generated.h"

UCLASS()
class AEROFIGHTERS_API ABasicEnemyPawn : public AEnemyPawn
{
	GENERATED_BODY()
	
public:
	ABasicEnemyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
