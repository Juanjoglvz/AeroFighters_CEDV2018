// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerProjectile.h"
#include "PlayerMissile.generated.h"

class AEnemy;
UCLASS()
class AEROFIGHTERS_API APlayerMissile : public APlayerProjectile
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerMissile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void ProjectileBehaviour(float DeltaTime) override;

	UPROPERTY()
		TWeakObjectPtr<AEnemy> LockedEnemy;
};
