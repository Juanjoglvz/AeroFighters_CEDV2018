// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyProjectile.h"
#include "EnemyMissile.generated.h"

UCLASS()
class AEROFIGHTERS_API AEnemyMissile : public AEnemyProjectile
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyMissile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void ProjectileBehaviour(float DeltaTime) override;
	
	// Override EnemyProjectile OnOverlap function, because missiles have to be destroyed if they impact with Player lasers too
	UFUNCTION(Category = "Hit")
		virtual void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

private:
	TWeakObjectPtr<ACharacter> CharacterReference;

};
