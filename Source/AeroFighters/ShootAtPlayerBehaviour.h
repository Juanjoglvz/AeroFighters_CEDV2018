// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBehaviour.h"
#include "UObject/NoExportTypes.h"
#include "ShootAtPlayerBehaviour.generated.h"

/**
 * 
 */
UCLASS()
class AEROFIGHTERS_API UShootAtPlayerBehaviour : public UProjectileBehaviour
{
	GENERATED_BODY()
	
public:
	UShootAtPlayerBehaviour();
	void Shoot(UWorld* World, FVector Location, FRotator Rotation, float DeltaTime) override;
};
