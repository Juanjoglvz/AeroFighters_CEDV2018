// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "MoveBehaviour.h"
#include "MoveLeft.h"
#include "MoveRight.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"

class AEnemy;

UCLASS()
class AEROFIGHTERS_API AEnemyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	//Variables for controlling the areas around the camera
	UPROPERTY()
		TWeakObjectPtr<AActor> TopMovableArea;
	UPROPERTY()
		TWeakObjectPtr<AActor> BottomMovableArea;
	UPROPERTY()
		TWeakObjectPtr<AActor> RightMovableArea;
	UPROPERTY()
		TWeakObjectPtr<AActor> LeftMovableArea;

	//Functions to spawn the different types of enemies
	void SpawnBug(FVector location, TSharedPtr<MoveBehaviour> Movement) const;


	//General function for spawning any type of enemy
	AEnemy* SpawnEnemy(FVector location, FRotator rotation) const;

	//Mesh references for the enemies
	UPROPERTY()
		UStaticMesh* BugShipMesh;

	//Move behaviours
	TSharedPtr<MoveRight> MoveRightObject;
	TSharedPtr<MoveLeft> MoveLeftObject;

	//Waves
	void Wave0() const;

};
