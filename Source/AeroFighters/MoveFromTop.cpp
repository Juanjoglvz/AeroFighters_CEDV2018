/* Copyright (C) 2018 Iván García, Juan José Corroto and Javier Córdoba - All Rights Reserved
* You may use, distribute and modify this code under the
* terms of the GNU GPLv3 license.
*
* You should have received a copy of the GNU GPLv3 license with
* this file. If not, please write to: ivan.garcia16@alu.uclm.es
*/

#include "MoveFromTop.h"

UMoveFromTop::UMoveFromTop()
{
	KeepMoving = true;
	TimeWaiting = 0.f;
}


void UMoveFromTop::SetUp(float MoveSpeed, UWorld* World, float MaxTimeWaiting, float StopPosition)
{
	Super::SetUp(MoveSpeed, World);
	this->MaxTimeWaiting = MaxTimeWaiting;
	this->StopPosition = StopPosition;
}

void UMoveFromTop::Move(FVector& CurrentPosition, float DeltaTime)
{
	if (KeepMoving)
	{
		FVector NewPos{ CurrentPosition.X, CurrentPosition.Y, CurrentPosition.Z };
		NewPos.X -= MoveSpeed * DeltaTime;
		if (NewPos.X < this->TopMovableArea->GetActorLocation().X - StopPosition)
		{
			KeepMoving = false;
		}

		CurrentPosition = NewPos;
	}
	else if (TimeWaiting > MaxTimeWaiting)
	{
		FVector NewPos{ CurrentPosition.X, CurrentPosition.Y, CurrentPosition.Z };
		NewPos.Y += MoveSpeed * DeltaTime;

		CurrentPosition = NewPos;
	}
	else
	{
		this->TimeWaiting += DeltaTime;
	}
}
