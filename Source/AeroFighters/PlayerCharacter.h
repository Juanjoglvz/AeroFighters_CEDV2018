/* Copyright (C) 2018 Iván García, Juan José Corroto and Javier Córdoba - All Rights Reserved
* You may use, distribute and modify this code under the
* terms of the GNU GPLv3 license.
*
* You should have received a copy of the GNU GPLv3 license with
* this file. If not, please write to: ivan.garcia16@alu.uclm.es
*/

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

	void IncreaseBombs();
	void IncreasePower();

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

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

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

	// Event thrown when the boss is destroyed
	DECLARE_DELEGATE(FBossDestroyed);
	FBossDestroyed MyBossDestroyed;

	// Widget to show the available bombs and lives
	UPROPERTY(EditAnywhere, Category = "Widgets")
		TSubclassOf<class UUserWidget> WBombs;

	UPROPERTY()
		class UUserWidget* pWBomb;

	UPROPERTY()
		class UTextBlock* pWBombText;

	UPROPERTY()
		class UTextBlock* pWHealthText;


	UPROPERTY(EditAnywhere, Category = "Widgets")
		TSubclassOf<class UUserWidget> WGameEnd;
	UPROPERTY()
		class UUserWidget* pWGameEnd;

	UPROPERTY(EditAnywhere, Category = "Widgets")
		TSubclassOf<class UUserWidget> WGameEndWinner;
	UPROPERTY()
		class UUserWidget* pWGameEndWinner;

	UPROPERTY(EditAnywhere, Category = "Widgets")
		TSubclassOf<class UUserWidget> WGameScore;
	UPROPERTY()
		class UUserWidget* pWGameScore;

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
	UPROPERTY(EditAnywhere, Category = "Player")
	unsigned int MaxNumberOfBombs;

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

	// Shooting sound
	UPROPERTY()
		UAudioComponent* shootingAudioComponent;
	UPROPERTY()
		UAudioComponent* crashAudioComponent;

	// PostProcessing Functionality
	UPostProcessComponent* PostProcessComponent;
	bool b_IsFlashing;
	float PostProcessingTimer;
	float FlashTime;

	// Function called when the boss is destroyed
	UFUNCTION()
		virtual void OnBossDestroyed();

	PlayerPower CurrentPower;
};
