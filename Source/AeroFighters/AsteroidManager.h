// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Asteroid.h"
#include "GameFramework/Actor.h"
#include "AsteroidManager.generated.h"

UCLASS()
class AEROFIGHTERS_API AAsteroidManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAsteroidManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, Category = "Intrinsic")
		int AsteroidCount;

	UPROPERTY(EditAnywhere, Category = "Intrinsic")
		float XInfLimit;

	UPROPERTY(EditAnywhere, Category = "Intrinsic")
		float XSupLimit;

	UPROPERTY(EditAnywhere, Category = "Intrinsic")
		float YInfLimit;

	UPROPERTY(EditAnywhere, Category = "Intrinsic")
		float YSupLimit;

	UPROPERTY(EditAnywhere, Category = "Intrinsic")
		float ZInfLimit;

	UPROPERTY(EditAnywhere, Category = "Intrinsic")
		float ZSupLimit;

	UPROPERTY(EditAnywhere, Category = "Intrinsic")
		float InfScale;

	UPROPERTY(EditAnywhere, Category = "Intrinsic")
		float SupScale;

	UPROPERTY(EditAnywhere, Category = "Intrinsic")
		float RotDriftSup;

	UPROPERTY(EditAnywhere, Category = "Intrinsic")
		float RotDriftSpeed;

private:
	float RandomFloat(float a, float b);
	AAsteroid* Prototype;
};
