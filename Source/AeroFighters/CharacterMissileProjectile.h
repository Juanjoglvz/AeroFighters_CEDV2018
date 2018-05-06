// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerProjectile.h"
#include "CharacterMissileProjectile.generated.h"

UCLASS()
class AEROFIGHTERS_API ACharacterMissileProjectile : public APlayerProjectile
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACharacterMissileProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Clone() override;

	virtual void ProjectileBehaviour(float DeltaTime) override;
};
