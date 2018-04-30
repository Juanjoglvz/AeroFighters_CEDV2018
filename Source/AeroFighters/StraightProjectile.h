// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.h"
#include "StraightProjectile.generated.h"

UCLASS()
class AEROFIGHTERS_API AStraightProjectile : public AProjectile
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStraightProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Clone() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;	

private:
	FVector ShotDirection;
};
