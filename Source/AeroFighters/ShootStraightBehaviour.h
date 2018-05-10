// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBehaviour.h"
#include "UObject/NoExportTypes.h"
#include "ShootStraightBehaviour.generated.h"

/**
 * 
 */
UCLASS()
class AEROFIGHTERS_API UShootStraightBehaviour : public UProjectileBehaviour
{
	GENERATED_BODY()
	
public:
	UShootStraightBehaviour();
	void Shoot(UWorld* World, FVector Location, FRotator Rotation, float DeltaTime) override;
};
