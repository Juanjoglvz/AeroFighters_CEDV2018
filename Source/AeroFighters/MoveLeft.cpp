// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveLeft.h"

UMoveLeft::UMoveLeft()
{
	KeepMoving = true;
	TimeWaiting = 0.f;
}

void UMoveLeft::SetUp(float MoveSpeed, UWorld* World, float MaxTimeWaiting)
{
	Super::SetUp(MoveSpeed, World);
	this->MaxTimeWaiting = MaxTimeWaiting;
}

void UMoveLeft::Move(FVector& CurrentPosition, float DeltaTime)
{
	if (KeepMoving || TimeWaiting > MaxTimeWaiting)
	{
		FVector NewPos{ CurrentPosition.X, CurrentPosition.Y, CurrentPosition.Z };
		NewPos.Y -= MoveSpeed * DeltaTime;
		if (NewPos.Y < this->LeftMovableArea->GetActorLocation().Y)
		{
			KeepMoving = false;
		}

		CurrentPosition = NewPos;
	}
	else
	{
		this->TimeWaiting += DeltaTime;
	}
}

