// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
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
	virtual void Move(FVector& CurrentPosition, float DeltaTime) PURE_VIRTUAL(UMoveBehaviour::Move, );

	void SetUp(float MoveSpeed, UWorld* World);

protected:
	float MoveSpeed;

	//Variables for controlling the areas where the player can move to
	UPROPERTY()
		TWeakObjectPtr<AActor> TopMovableArea;
	UPROPERTY()
		TWeakObjectPtr<AActor> BottomMovableArea;
	UPROPERTY()
		TWeakObjectPtr<AActor> RightMovableArea;
	UPROPERTY()
		TWeakObjectPtr<AActor> LeftMovableArea;
};
