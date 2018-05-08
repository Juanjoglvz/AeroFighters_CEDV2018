// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveLeft.h"

MoveLeft::MoveLeft(float MoveSpeed) : MoveSpeed(MoveSpeed)
{
}

FVector MoveLeft::Move(FVector CurrentPosition, float DeltaTime) const
{
	FVector NewPos(CurrentPosition.X, CurrentPosition.Y, CurrentPosition.Z);
	NewPos.Y -= MoveSpeed * DeltaTime;
	return NewPos;
}
