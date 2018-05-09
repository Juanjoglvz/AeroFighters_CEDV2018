// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveRight.h"

UMoveRight::UMoveRight()
{
}

void UMoveRight::Move(FVector& CurrentPosition, float DeltaTime, UWorld* World) const
{
	FVector NewPos{ CurrentPosition.X, CurrentPosition.Y, CurrentPosition.Z };
	NewPos.Y += MoveSpeed * DeltaTime;

	CurrentPosition = NewPos;
}
