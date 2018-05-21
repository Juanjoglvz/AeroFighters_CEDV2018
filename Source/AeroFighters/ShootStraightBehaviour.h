/* Copyright (C) 2018 Iván García, Juan José Corroto and Javier Córdoba - All Rights Reserved
* You may use, distribute and modify this code under the
* terms of the GNU GPLv3 license.
*
* You should have received a copy of the GNU GPLv3 license with
* this file. If not, please write to: ivan.garcia16@alu.uclm.es
*/

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBehaviour.h"
#include "UObject/NoExportTypes.h"
#include "ShootStraightBehaviour.generated.h"

/**
 * 
 */
UCLASS()
class AEROFIGHTERS_API UShootStraightBehaviour : public UProjectileBehaviour
{
	GENERATED_BODY()
	
public:
	UShootStraightBehaviour();
	void Shoot(UWorld* World, FVector Location, FRotator Rotation, float DeltaTime) override;
};
