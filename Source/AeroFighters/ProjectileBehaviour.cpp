// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileBehaviour.h"

void UProjectileBehaviour::SetUp(UWorld* World, float ShootTimer)
{
	this->ShootTimer = ShootTimer;
	this->World = World;
}

