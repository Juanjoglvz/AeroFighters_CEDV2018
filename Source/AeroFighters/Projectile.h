// Fill out your copyright notice in the Description page of Project Settings.

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
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;	

	void SetSpeed (float Speed_) { Speed = Speed_; }
	float GetSpeed() const { return Speed;  }

private:
	float Speed;
};
