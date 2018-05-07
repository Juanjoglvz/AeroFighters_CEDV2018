// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class AEROFIGHTERS_API MoveBehaviour
{
public:
	MoveBehaviour();

	virtual FVector Move(FVector CurrentPosition, float DeltaTime) const = 0;
};
