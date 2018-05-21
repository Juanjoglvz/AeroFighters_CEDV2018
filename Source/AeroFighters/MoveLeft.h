/* Copyright (C) 2018 Iv�n Garc�a, Juan Jos� Corroto and Javier C�rdoba - All Rights Reserved
* You may use, distribute and modify this code under the
* terms of the GNU GPLv3 license.
*
* You should have received a copy of the GNU GPLv3 license with
* this file. If not, please write to: ivan.garcia16@alu.uclm.es
*/

#pragma once

#include "CoreMinimal.h"
#include "MoveBehaviour.h"
#include "MoveLeft.generated.h"

/**
 * 
 */
UCLASS()
class AEROFIGHTERS_API UMoveLeft : public UMoveBehaviour
{
	GENERATED_BODY()
	
public:
	UMoveLeft();
	
	void Move(FVector& CurrentPosition, float DeltaTime) override;

	void SetUp(float MoveSpeed, UWorld* World, float MaxTimeWaiting);

private:
	bool KeepMoving;
	float TimeWaiting;
	float MaxTimeWaiting;
};
