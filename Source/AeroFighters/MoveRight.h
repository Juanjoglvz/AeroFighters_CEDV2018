// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MoveBehaviour.h"

/**
 * 
 */
class AEROFIGHTERS_API MoveRight : public MoveBehaviour
{
public:
	MoveRight(float MoveSpeed);

	FVector Move(FVector CurrentPosition, float DeltaTime) const override;

private:
	float MoveSpeed;
};
