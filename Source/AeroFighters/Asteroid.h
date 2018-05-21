/* Copyright (C) 2018 Iván García, Juan José Corroto and Javier Córdoba - All Rights Reserved
* You may use, distribute and modify this code under the
* terms of the GNU GPLv3 license.
*
* You should have received a copy of the GNU GPLv3 license with
* this file. If not, please write to: ivan.garcia16@alu.uclm.es
*/

#pragma once

#include "Core.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "Asteroid.generated.h"

UCLASS()
class AEROFIGHTERS_API AAsteroid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAsteroid();

	UPROPERTY()
		UStaticMeshComponent* StaticMeshComponent;

	virtual AAsteroid* clone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetRotationDrift(FRotator RDrift);
	void SetRotationDriftSpeed(float speed);

private:
	FRotator RotationDrift;
	float RotationDriftSpeed;
	
};
