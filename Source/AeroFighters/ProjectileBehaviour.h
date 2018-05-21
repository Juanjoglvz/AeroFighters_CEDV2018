/* Copyright (C) 2018 Iván García, Juan José Corroto and Javier Córdoba - All Rights Reserved
* You may use, distribute and modify this code under the
* terms of the GNU GPLv3 license.
*
* You should have received a copy of the GNU GPLv3 license with
* this file. If not, please write to: ivan.garcia16@alu.uclm.es
*/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ProjectileBehaviour.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class AEROFIGHTERS_API UProjectileBehaviour : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void Shoot(UWorld* World, FVector Location, FRotator Rotation, float DeltaTime) PURE_VIRTUAL(UProjectileBehaviour::Shoot, );

protected:
	float ShootTimer;
	float Timer;
};
