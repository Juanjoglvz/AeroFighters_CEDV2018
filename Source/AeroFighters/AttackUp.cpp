// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackUp.h"


AAttackUp::AAttackUp() : Super()
{
	PrimaryActorTick.bCanEverTick = true;

	auto StaticMeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Assets/Powerup/electricity.electricity'"));

	if (StaticMeshAsset.Succeeded())
	{
		SetStaticMeshAsset(StaticMeshAsset.Object);
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
