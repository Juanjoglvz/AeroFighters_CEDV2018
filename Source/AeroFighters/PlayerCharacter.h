// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "DelegateCombinations.h"
#include "Engine.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UENUM(BlueprintType)
enum class PlayerPower : uint8
{
	BasicShot,
	WideShot,
	WideShotMissile,
	FullPower,
};

UCLASS()
class AEROFIGHTERS_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Input Variable
	FVector2D MovementInput;

	// Input Functions
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	// Function called when character spawns a bomb
	void ThrowABomb();

	// Function called when character press the Shooting key
	void Shoot();

	// Function called when character releases the Shooting key
	void StopShooting();

	UFUNCTION(BlueprintCallable, Category="Overlap")
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor);

	TSubclassOf<class AEnemyProjectile> ProjectileClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// Static Mesh 
	UPROPERTY(BlueprintReadOnly, Category="StaticMeshComponent")
		UStaticMeshComponent* StaticMeshComponent;

	// Delegate needed to observer pattern
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDiscardEnemyShootsDelegate);
	FDiscardEnemyShootsDelegate myDiscardEnemyShootsDelegate;

private:
	UPROPERTY(EditAnywhere)
		float MoveSpeed;
	UPROPERTY(EditAnywhere)
		FVector CameraSpeed;

	// Variables for controlling the areas where the player can move to
	UPROPERTY()
		TWeakObjectPtr<AActor> TopMovableArea;
	UPROPERTY()
		TWeakObjectPtr<AActor> BottomMovableArea;
	UPROPERTY()
		TWeakObjectPtr<AActor> RightMovableArea;
	UPROPERTY()
		TWeakObjectPtr<AActor> LeftMovableArea;

	// Reference to RecordManager
	UPROPERTY()
		TWeakObjectPtr<class ARecordsManager> RecordsManagerReference;

	UPROPERTY(EditAnywhere)
		unsigned int NumberOfBombsAvailable;
	UPROPERTY(EditAnywhere, Category = "Player")
		unsigned int NumberOfLives;

	// Function to see if posible to move
	bool IsPosMoveX(FVector NewPos) const;
	bool IsPosMoveY(FVector NewPos) const;

	// Shooting functionality
	void Shoot(float DeltaTime);
	bool b_IsShooting;
	float ShootTimer;
	float MissileTimer;
	float MissileMaxTime;
	float Timer;

	// Invulnerabilty 
	bool b_IsVulnerable;
	float VulnerableTimer;
	float MaximumVulnerabilityTime;
	float ShowAndHideTimer;

	PlayerPower CurrentPower;
};
