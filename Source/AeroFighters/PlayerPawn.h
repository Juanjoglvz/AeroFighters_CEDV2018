// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "EnemyProjectile.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class AEROFIGHTERS_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Input Variable
	FVector2D MovementInput;

	//Input Functions
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	UFUNCTION()
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	TSubclassOf<AEnemyProjectile> ProjectileClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Skeletal Mesh 
	UPROPERTY()
		UStaticMeshComponent* StaticMeshComponent;

private:
	UPROPERTY(EditAnywhere)
		float MoveSpeed;
	UPROPERTY(EditAnywhere)
		FVector CameraSpeed;

	//Variables for controlling the areas where the player can move to
	UPROPERTY()
		TWeakObjectPtr<AActor> TopMovableArea;
	UPROPERTY()
		TWeakObjectPtr<AActor> BottomMovableArea;
	UPROPERTY()
		TWeakObjectPtr<AActor> RightMovableArea;
	UPROPERTY()
		TWeakObjectPtr<AActor> LeftMovableArea;
	//Function to see if posible to move
	bool IsPosMoveX(FVector NewPos) const;
	bool IsPosMoveY(FVector NewPos) const;
};
