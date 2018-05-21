/* Copyright (C) 2018 Iván García, Juan José Corroto and Javier Córdoba - All Rights Reserved
* You may use, distribute and modify this code under the
* terms of the GNU GPLv3 license.
*
* You should have received a copy of the GNU GPLv3 license with
* this file. If not, please write to: ivan.garcia16@alu.uclm.es
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS(Abstract)
class AEROFIGHTERS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void ProjectileBehaviour(float DeltaTime) PURE_VIRTUAL(AProjectile::ProjectileBehaviour, );

	virtual void SetStaticMeshAsset (UStaticMesh* StaticMeshAsset);
	 
	UPROPERTY()
		UStaticMeshComponent* StaticMesh;
	
	// Reference to movable areas
	UPROPERTY()
		TWeakObjectPtr<AActor> BottomMovableArea;
	UPROPERTY()
		TWeakObjectPtr<AActor> TopMovableArea;
	UPROPERTY()
		TWeakObjectPtr<AActor> RightMovableArea;
	UPROPERTY()
		TWeakObjectPtr<AActor> LeftMovableArea;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;	

	void SetSpeed (float Speed_) { Speed = Speed_; }
	float GetSpeed() const { return Speed;  }

	UStaticMeshComponent* GetStaticMesh() const { return StaticMesh; }

private:
	float Speed;
};
