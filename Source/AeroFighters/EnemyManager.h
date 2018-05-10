// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "MoveBehaviour.h"
#include "MoveLeft.h"
#include "MoveRight.h"
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
		int NumberLeft;
	UPROPERTY(EditAnywhere, Category = "Wave")
		int NumberRight;
	UPROPERTY(EditAnywhere, Category = "Wave")
		int NumberTop;

	UPROPERTY(EditAnywhere, Category = "Wave")
		float SeparationLeft;
	UPROPERTY(EditAnywhere, Category = "Wave")
		float SeparationRight;
	UPROPERTY(EditAnywhere, Category = "Wave")
		float SeparationTop;

	UPROPERTY(EditAnywhere, Category = "Wave")
		float PositionXLeft;
	UPROPERTY(EditAnywhere, Category = "Wave")
		float PositionXRight;

	//Variables for controlling wave behaviour
	UPROPERTY(EditAnywhere, Category = "WaveBehaviour")
		float MoveRightSpeed;
	UPROPERTY(EditAnywhere, Category = "WaveBehaviour")
		float MoveLeftSpeed;
	UPROPERTY(EditAnywhere, Category = "WaveBehaviour")
		float MoveRightMaxWaitingTime;
	UPROPERTY(EditAnywhere, Category = "WaveBehaviour")
		float MoveLeftMaxWaitingTime;

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


	// General function for spawning any type of enemy
	AEnemy* SpawnEnemy(FVector location, FRotator rotation) const;

	// Mesh references for the enemies
	UPROPERTY()
		UStaticMesh* BugShipMesh;

	//Move behaviours
	UPROPERTY()
		UMoveRight* MoveRightObject;
	UPROPERTY()
		UMoveLeft* MoveLeftObject;

	// Projectile Behaviours
	UPROPERTY()
		UShootAtPlayerBehaviour* ShootAtPlayerObject;
	UPROPERTY()
		UShootStraightBehaviour* ShootStraightObject;
	UPROPERTY()
		UMissileBehaviour* MissileObject;

	// Wave
	UFUNCTION(BlueprintCallable)
		void Wave() const;

};
