// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "Asteroid.generated.h"

UCLASS()
class AEROFIGHTERS_API AAsteroid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAsteroid();

	UPROPERTY()
		UStaticMeshComponent* StaticMeshComponent;

	virtual AAsteroid* clone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetRotationDrift(FRotator RDrift);
	void SetRotationDriftSpeed(float speed);

private:
	FRotator RotationDrift;
	float RotationDriftSpeed;
	
};
