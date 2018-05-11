// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveRight.h"

UMoveRight::UMoveRight()
{
	KeepMoving = true;
	TimeWaiting = 0.f;
}

void UMoveRight::SetUp(float MoveSpeed, UWorld* World, float MaxTimeWaiting)
{
	Super::SetUp(MoveSpeed, World);
	this->MaxTimeWaiting = MaxTimeWaiting;
}

void UMoveRight::Move(FVector& CurrentPosition, float DeltaTime)
{
	if (KeepMoving || TimeWaiting > MaxTimeWaiting)
	{
		FVector NewPos{ CurrentPosition.X, CurrentPosition.Y, CurrentPosition.Z };
		NewPos.Y += MoveSpeed * DeltaTime;

		if (NewPos.Y > this->RightMovableArea->GetActorLocation().Y)
		{
			this->KeepMoving = false;
		}

		CurrentPosition = NewPos;
	}
	else
	{
		TimeWaiting += DeltaTime;
	}

}
