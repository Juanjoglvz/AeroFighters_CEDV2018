// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
 
#include "CoreMinimal.h"
#include "Engine.h"
#include "GameFramework/Pawn.h"
#include "Boss.generated.h"

class UMoveBehaviour;

UCLASS()
class AEROFIGHTERS_API ABoss : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABoss();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY()
		UStaticMeshComponent* StaticMeshComponent;

	UFUNCTION(BlueprintCallable)
		void SetPosition(AActor* Position);
	UFUNCTION(BlueprintCallable)
		void Enrage();

	UFUNCTION(BlueprintCallable)
		void LaserCircle();
	UFUNCTION(BlueprintCallable)
		void MissileWave();
	UFUNCTION(BlueprintCallable)
		void BugSpawn();

	

	
private:

	FVector CameraSpeed;
	UPROPERTY()
		AActor* Position;

	float Hp;
	float LaserDmg;
	float MissileDmg;
	bool b_Enraged;

	bool b_LaserCircle;
	float LaserTimer;
	float LTimer;
	uint32 CurrentLaser;
	void LaserAttack();

	bool b_MissileWave;
	float MissileTimer;
	float MTimer;
	uint32 CurrentMissile;
	void MissileAttack();

	bool b_BugSpawn;
	float BugSpawnTimer;
	float BTimer;
	uint32 BugsSpawned;
	void SpawnBugWave();
	void SpawnBug(FVector Location, UMoveBehaviour* Movement) const;

	// Mesh references for the enemies
	UPROPERTY()
		UStaticMesh* BugShipMesh;
};
