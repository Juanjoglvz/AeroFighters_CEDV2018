/* Copyright (C) 2018 Iván García, Juan José Corroto and Javier Córdoba - All Rights Reserved
* You may use, distribute and modify this code under the
* terms of the GNU GPLv3 license.
*
* You should have received a copy of the GNU GPLv3 license with
* this file. If not, please write to: ivan.garcia16@alu.uclm.es
*/

#pragma once
 
#include "CoreMinimal.h"
#include "Engine.h"
#include "BehaviorTree/BehaviorTree.h"

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

	float GetHp();

	UBehaviorTree* BehaviorTree;

	
private:

	FVector CameraSpeed;
	UPROPERTY()
		AActor* Position;

	UFUNCTION()
		virtual void OnBomb();

	float Hp;
	float LaserDmg;
	float MissileDmg;
	float BombDmg;
	bool b_Enraged;

	bool b_LaserCircle;
	float LaserTimer;
	float LTimer;
	int32 CurrentLaser;
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
