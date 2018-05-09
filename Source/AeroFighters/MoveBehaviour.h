// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EngineMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MoveBehaviour.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class AEROFIGHTERS_API UMoveBehaviour : public UObject
{
	GENERATED_BODY()

public:
	virtual void Move(FVector& CurrentPosition, float DeltaTime, UWorld* World) const PURE_VIRTUAL(UMoveBehaviour::Move, );

	void SetSpeed(float MoveSpeed);

protected:
	float MoveSpeed;
};
