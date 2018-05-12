// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "MoveBehaviour.h"
#include "MoveLeft.h"
#include "MoveRight.h"
#include "MoveFromTop.h"
#include "ProjectileBehaviour.h"
#include "ShootAtPlayerBehaviour.h"
#include "ShootStraightBehaviour.h"
#include "MissileBehaviour.h"
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

	// Variables for controlling wave spawning
	UPROPERTY(EditAnywhere, Category = "Wave")
		FString EnemyType;

	UPROPERTY(EditAnywhere, Category = "Wave")
		int NumberLeft;
	UPROPERTY(EditAnywhere, Category = "Wave")
		int NumberRight;
	UPROPERTY(EditAnywhere, Category = "Wave")
		int NumberTop;

	UPROPERTY(EditAnywhere, Category = "WaveLeft")
		float SeparationLeft;
	UPROPERTY(EditAnywhere, Category = "WaveLeft")
		float PositionXLeft;
	UPROPERTY(EditAnywhere, Category = "WaveLeft")
		float MoveLeftSpeed;
	UPROPERTY(EditAnywhere, Category = "WaveLeft")
		float MoveLeftMaxWaitingTime;

	UPROPERTY(EditAnywhere, Category = "WaveRight")
		float SeparationRight;
	UPROPERTY(EditAnywhere, Category = "WaveRight")
		float PositionXRight;
	UPROPERTY(EditAnywhere, Category = "WaveRight")
		float MoveRightSpeed;
	UPROPERTY(EditAnywhere, Category = "WaveRight")
		float MoveRightMaxWaitingTime;

	UPROPERTY(EditAnywhere, Category = "WaveTop")
		float SeparationTop;
	UPROPERTY(EditAnywhere, Category = "WaveTop")
		float PositionYTop;
	UPROPERTY(EditAnywhere, Category = "WaveTop")
		float MoveTopSpeed;
	UPROPERTY(EditAnywhere, Category = "WaveTop")
		float MoveTopMaxWaitingTime;
	UPROPERTY(EditAnywhere, Category = "WaveTop")
		float StopPosition;

private:
	// Variables for controlling the areas around the camera
	UPROPERTY()
		TWeakObjectPtr<AActor> TopMovableArea;
	UPROPERTY()
		TWeakObjectPtr<AActor> BottomMovableArea;
	UPROPERTY()
		TWeakObjectPtr<AActor> RightMovableArea;
	UPROPERTY()
		TWeakObjectPtr<AActor> LeftMovableArea;

	// Functions to spawn the different types of enemies
	void SpawnBug(FVector location, UMoveBehaviour* Movement, UProjectileBehaviour* ProjectileBehaviour) const;
	void SpawnShip(FVector location, UMoveBehaviour* Movement, UProjectileBehaviour* ProjectileBehaviour) const;

	// General function for spawning any type of enemy
	AEnemy* SpawnEnemy(FVector location, FRotator rotation) const;

	// Mesh references for the enemies
	UPROPERTY()
		UStaticMesh* BugShipMesh;
	UPROPERTY()
		UStaticMesh* ShipMesh;

	//Move behaviours
	UPROPERTY()
		UMoveRight* MoveRightObject;
	UPROPERTY()
		UMoveLeft* MoveLeftObject;
	UPROPERTY()
		UMoveFromTop* MoveFromTopObject;

	// Wave
	UFUNCTION(BlueprintCallable)
		void Wave() const;

};
