// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "MoveBehaviour.h"
#include "Powerup.h"
#include "RecordsManager.h"
#include "ProjectileBehaviour.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class AEROFIGHTERS_API AEnemy : public AActor
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		virtual void OnBomb();

	float PowerupSpawnProbability;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Set the mesh in runtime
	void SetStaticMesh(UStaticMesh* mesh);

	//Set the enemy behaviours
	void SetMoveBehaviour(UMoveBehaviour* Move);

	void SetProjectileBehaviour(UProjectileBehaviour* ProjectileBehaviour_) { ProjectileBehaviour = ProjectileBehaviour_; }

	// Set Drop type and HP
	void SetHp(int32 HP);

	void SetPowerupType(TSubclassOf<class APowerup> PowerupType);

	TWeakObjectPtr<class ARecordsManager> RecordsManagerReference;



private:
	void GetRecordsManager();

	UPROPERTY()
		UStaticMeshComponent* StaticMeshComponent;
	
	UPROPERTY()
		UMoveBehaviour* Movement;

	UPROPERTY()
		UProjectileBehaviour* ProjectileBehaviour;

	FVector CameraSpeed;

	TSubclassOf<class APowerup> PowerupType;

	// Variables for controlling HP
	int32 HP;
	int32 LaserDmg;
	int32 MissileDmg;
};
