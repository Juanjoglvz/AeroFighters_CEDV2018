// Fill out your copyright notice in the Description page of Project Settings.

#include "AsteroidManager.h"
#include <stdlib.h>  

// Sets default values
AAsteroidManager::AAsteroidManager() : AsteroidCount(400)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAsteroidManager::BeginPlay()
{
	Super::BeginPlay();

	AAsteroid* a = GetWorld()->SpawnActor<AAsteroid>(AAsteroid::StaticClass());

	Prototype = a;
	
	AAsteroid* nAst = a;

	for (int i = 0; i < AsteroidCount; i++)
	{
		FVector Location(RandomFloat(XInfLimit, XSupLimit), RandomFloat(YInfLimit, YSupLimit), RandomFloat(ZInfLimit, ZSupLimit));
		FRotator Rotation(RandomFloat(0, 360), RandomFloat(0, 360), RandomFloat(0, 360));

		float sc = RandomFloat(InfScale, SupScale);
		FVector Scale(sc, sc, sc);

		FTransform transform(Rotation, Location, Scale);
		
		FRotator RDrift(RandomFloat(0, RotDriftSup), RandomFloat(0, RotDriftSup), RandomFloat(0, RotDriftSup));

		nAst->SetActorTransform(transform);
		nAst->SetRotationDrift(RDrift);
		nAst->SetRotationDriftSpeed(RotDriftSpeed);

		nAst = Prototype->clone();

	}
	
}

// Called every frame
void AAsteroidManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


float AAsteroidManager::RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

