/* Copyright (C) 2018 Iván García, Juan José Corroto and Javier Córdoba - All Rights Reserved
* You may use, distribute and modify this code under the
* terms of the GNU GPLv3 license.
*
* You should have received a copy of the GNU GPLv3 license with
* this file. If not, please write to: ivan.garcia16@alu.uclm.es
*/

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "UObject/NoExportTypes.h"
#include "MoveBehaviour.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class AEROFIGHTERS_API UMoveBehaviour : public UObject
{
	GENERATED_BODY()

public:
	virtual void Move(FVector& CurrentPosition, float DeltaTime) PURE_VIRTUAL(UMoveBehaviour::Move, );

	void SetUp(float MoveSpeed, UWorld* World);

protected:
	float MoveSpeed;

	//Variables for controlling the areas where the player can move to
	UPROPERTY()
		TWeakObjectPtr<AActor> TopMovableArea;
	UPROPERTY()
		TWeakObjectPtr<AActor> BottomMovableArea;
	UPROPERTY()
		TWeakObjectPtr<AActor> RightMovableArea;
	UPROPERTY()
		TWeakObjectPtr<AActor> LeftMovableArea;
};
