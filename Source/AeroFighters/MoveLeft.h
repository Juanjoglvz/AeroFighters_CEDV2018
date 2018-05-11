// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MoveBehaviour.h"
#include "MoveLeft.generated.h"

/**
 * 
 */
UCLASS()
class AEROFIGHTERS_API UMoveLeft : public UMoveBehaviour
{
	GENERATED_BODY()
	
public:
	UMoveLeft();
	
	void Move(FVector& CurrentPosition, float DeltaTime) override;

	void SetUp(float MoveSpeed, UWorld* World, float MaxTimeWaiting);

private:
	bool KeepMoving;
	float TimeWaiting;
	float MaxTimeWaiting;
};
