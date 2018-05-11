// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MoveBehaviour.h"
#include "MoveFromTop.generated.h"

/**
 * 
 */
UCLASS()
class AEROFIGHTERS_API UMoveFromTop : public UMoveBehaviour
{
	GENERATED_BODY()
	
public:
	UMoveFromTop();

	void Move(FVector& CurrentPosition, float DeltaTime) override;

	void SetUp(float MoveSpeed, UWorld* World, float MaxTimeWaiting, float StopPosition);

private:
	bool KeepMoving;
	float TimeWaiting;
	float MaxTimeWaiting;
	float StopPosition;
};
