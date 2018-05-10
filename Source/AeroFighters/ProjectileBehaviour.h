// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ProjectileBehaviour.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class AEROFIGHTERS_API UProjectileBehaviour : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void Shoot(UWorld* World, FVector Location, FRotator Rotation, float DeltaTime) PURE_VIRTUAL(UProjectileBehaviour::Shoot, );

protected:
	float ShootTimer;
	float Timer;
};
