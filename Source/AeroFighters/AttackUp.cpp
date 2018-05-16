// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackUp.h"


AAttackUp::AAttackUp() : Super()
{
	PrimaryActorTick.bCanEverTick = true;

	auto StaticMeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Assets/Powerup/attackup.attackup'"));

	if (StaticMeshAsset.Succeeded())
	{
		SetStaticMeshAsset(StaticMeshAsset.Object);
		SetActorScale3D(FVector(0.1, 0.1, 0.1));
	}
}

void AAttackUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAttackUp::CollisionAction(APlayerCharacter* Character)
{
	if (Character)
	{
		Character->IncreasePower();
	}
}
