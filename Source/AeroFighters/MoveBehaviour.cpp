// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveBehaviour.h"

void UMoveBehaviour::SetUp(float MoveSpeed, UWorld* World)
{
	this->MoveSpeed = MoveSpeed;

	//Get The references to the borders
	FString TopMovableAreaString = FString(TEXT("TopMovableArea"));
	FString BottomMovableAreaString = FString(TEXT("BottomMovableArea"));
	FString RightMovableAreaString = FString(TEXT("RightMovableArea"));
	FString LeftMovableAreaString = FString(TEXT("LeftMovableArea"));
	uint32 i = 0;
	for (TActorIterator<AActor> itr(World); itr; ++itr)
	{
		if (TopMovableAreaString.Equals(itr->GetName()))
		{
			this->TopMovableArea = *itr;
			i++;
		}
		else if (BottomMovableAreaString.Equals(itr->GetName()))
		{
			this->BottomMovableArea = *itr;
			i++;
		}
		else if (RightMovableAreaString.Equals(itr->GetName()))
		{
			this->RightMovableArea = *itr;
			i++;
		}
		else if (LeftMovableAreaString.Equals(itr->GetName()))
		{
			this->LeftMovableArea = *itr;
			i++;
		}

		if (i > 3)
		{
			break;
		}
	}
}
