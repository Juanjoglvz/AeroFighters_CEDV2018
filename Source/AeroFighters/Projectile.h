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

	virtual void Clone() PURE_VIRTUAL(AProjectile::Clone, );

	virtual void SetStaticMeshAsset (UStaticMesh* StaticMeshAsset);
	 
	UPROPERTY()
		UStaticMeshComponent* StaticMesh;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;	

	void SetSpeed (float Speed_) { Speed = Speed_; }
	float GetSpeed() const { return Speed;  }

private:
	float Speed;
};
