// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "PlayerCharacter.h"
#include "GameFramework/Actor.h"
#include "Powerup.generated.h"

UCLASS(Abstract)
class AEROFIGHTERS_API APowerup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerup();
	void SetSpeed(float MoveSpeed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

	float MoveSpeed;
	//Variables for controlling the areas where the player can move to
	UPROPERTY()
		TWeakObjectPtr<AActor> TopMovableArea;
	UPROPERTY()
		TWeakObjectPtr<AActor> BottomMovableArea;
	UPROPERTY()
		TWeakObjectPtr<AActor> RightMovableArea;
	UPROPERTY()
		TWeakObjectPtr<AActor> LeftMovableArea;

	TWeakObjectPtr<AActor> LastCollidedArea;

	virtual void SetStaticMeshAsset(UStaticMesh* StaticMeshAsset);
	UPROPERTY()
		UStaticMeshComponent* StaticMeshComponent;

	virtual void CollisionAction(APlayerCharacter* Character) PURE_VIRTUAL(APowerup::CollisionAction, );

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	virtual void Move(float DeltaTime);
	void SetUp(UWorld* World);
	float RandomFloat(float a, float b);
	void ChangeDirection(FVector Position);

	FVector CameraSpeed;
	FVector Direction;
};
