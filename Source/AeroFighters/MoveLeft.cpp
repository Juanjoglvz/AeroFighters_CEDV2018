// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveLeft.h"

UMoveLeft::UMoveLeft()
{
}

void UMoveLeft::Move(FVector& CurrentPosition, float DeltaTime, UWorld* World) const
{
	FVector NewPos{ CurrentPosition.X, CurrentPosition.Y, CurrentPosition.Z };
	NewPos.Y -= MoveSpeed * DeltaTime;

	CurrentPosition = NewPos;
}

