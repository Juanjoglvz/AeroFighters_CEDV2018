/* Copyright (C) 2018 Iván García, Juan José Corroto and Javier Córdoba - All Rights Reserved
* You may use, distribute and modify this code under the
* terms of the GNU GPLv3 license.
*
* You should have received a copy of the GNU GPLv3 license with
* this file. If not, please write to: ivan.garcia16@alu.uclm.es
*/

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
