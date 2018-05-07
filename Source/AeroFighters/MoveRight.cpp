// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveRight.h"

MoveRight::MoveRight(float MoveSpeed) : MoveSpeed(100.f)
{
}


FVector MoveRight::Move(FVector CurrentPosition,float DeltaTime) const
{
	FVector NewPos(CurrentPosition.X, CurrentPosition.Y, CurrentPosition.Z);
	NewPos.Y += MoveSpeed * DeltaTime;
	return NewPos;
}
