// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBehaviour.h"
#include "UObject/NoExportTypes.h"
#include "MissileBehaviour.generated.h"

/**
 * 
 */
UCLASS()
class AEROFIGHTERS_API UMissileBehaviour : public UProjectileBehaviour
{
	GENERATED_BODY()
	
public:
	UMissileBehaviour();
	void Shoot(UWorld* World, FVector Location, FRotator Rotation, float DeltaTime) override;

};
