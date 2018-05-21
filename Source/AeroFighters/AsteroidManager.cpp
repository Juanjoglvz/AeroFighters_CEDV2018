/* Copyright (C) 2018 Iván García, Juan José Corroto and Javier Córdoba - All Rights Reserved
* You may use, distribute and modify this code under the
* terms of the GNU GPLv3 license.
*
* You should have received a copy of the GNU GPLv3 license with
* this file. If not, please write to: ivan.garcia16@alu.uclm.es
*/

#include "AsteroidManager.h"
#include <stdlib.h>  

// Sets default values
AAsteroidManager::AAsteroidManager() : AsteroidCount(400), Prototype(nullptr), ClosestAsteroid(FVector(0.0f, 0.0f, 0.0f)), ViewportSize(FVector2D(0.0f, 0.0f)),
									AccumulatedDeltaTime(0.0f), RefreshFrequency(0.5f), LookaheadSpawnDistance(300.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAsteroidManager::BeginPlay()
{
	Super::BeginPlay();

	if (!AsteroidType)
	{
		UE_LOG(LogTemp, Error, TEXT("Null asteroid type, exiting"));
		return;
	}

	if (AsteroidCount <= 0)
		return;

	GenerateRandomPositions();

	SpawnVisibleAsteroids();
}

AAsteroid* AAsteroidManager::SpawnRandomAsteroid(FVector Location)
{
	AAsteroid* NewAsteroid;
	if (Prototype == nullptr)
	{
		Prototype = GetWorld()->SpawnActor<AAsteroid>(AsteroidType);
		NewAsteroid = Prototype;
	}
	else
	{
		NewAsteroid = Prototype->clone();
	}

	FRotator Rotation(RandomFloat(-90, 90), RandomFloat(-90, 90), RandomFloat(-90, 90));

	float sc = RandomFloat(InfScale, SupScale);
	FVector Scale(sc, sc, sc);

	FTransform transform(Rotation, Location, Scale);

	FRotator RDrift(RandomFloat(0, RotDriftSup), RandomFloat(0, RotDriftSup), RandomFloat(0, RotDriftSup));

	NewAsteroid->SetActorTransform(transform);
	NewAsteroid->SetRotationDrift(RDrift);
	NewAsteroid->SetRotationDriftSpeed(RotDriftSpeed);

	NewAsteroid = Prototype->clone();

	return NewAsteroid;
}

void AAsteroidManager::SpawnVisibleAsteroids()
{
	bool Spawned = false;
	int Index = 0;
	while (Index < AsteroidPositions.Num())
	{
		FVector Location = AsteroidPositions[Index];

		if (IsPositionOnScreen(Location))
		{
			AAsteroid* SpawnedAsteroid = SpawnRandomAsteroid(Location);
			AsteroidPositions.RemoveSingle(Location);
			SpawnedAsteroids.Add(SpawnedAsteroid);
			Spawned = true;
			UE_LOG(LogTemp, Display, TEXT("Spawned at X:%f  Y:%f"), Location.X, Location.Y);
		}
		/*else if (Spawned) // If we spawned an asteroid and we found an asteroid that is not on screen then stop trying spawning new ones
		{
			break;
		}*/
		else {
			Index++;
		}
	}

	if (Spawned)
		SpawnedAsteroids.Sort([](const AAsteroid& a1, const AAsteroid& a2) {return a1.GetActorLocation().X < a2.GetActorLocation().X; });
}

void AAsteroidManager::DespawnInvisibleAsteroids()
{
	bool Despawned = false;
	int Index = 0;
	while (Index < SpawnedAsteroids.Num())
	{
		AAsteroid* ast = SpawnedAsteroids[Index];
		if (ast == Prototype)
		{
			SpawnedAsteroids.RemoveSingle(ast);
			continue;
		}

		FVector Location = ast->GetActorLocation();

		if (!IsPositionOnScreen(Location))
		{
			ast->Destroy();
			SpawnedAsteroids.RemoveSingle(ast);
			Despawned = true;
			UE_LOG(LogTemp, Display, TEXT("Despawned %p at X:%f  Y:%f"), ast, Location.X, Location.Y);
		}
		/*else if (Despawned) // If we despawned an asteroid and we found an asteroid that is on screen then stop trying despawning new ones
		{
			break;
		}*/
		else
		{
			Index++;
		}
	}
}

void AAsteroidManager::GenerateRandomPositions()
{
	for (int i = 0; i < AsteroidCount; i++)
	{
		FVector Location(RandomFloat(XInfLimit, XSupLimit), RandomFloat(YInfLimit, YSupLimit), RandomFloat(ZInfLimit, ZSupLimit));

		AsteroidPositions.Add(Location);
	}

	AsteroidPositions.Sort([](FVector v1, FVector v2) {return v1.X < v2.X; });
}

bool AAsteroidManager::IsPositionOnScreen(FVector position)
{
	FVector2D ScreenPosition = FVector2D();
	bool IsPositionOnScreen = UGameplayStatics::GetPlayerController(GetWorld(), 0)->ProjectWorldLocationToScreen(position, ScreenPosition, false);
	if (ViewportSize.X == 0) // Will this change during game execution?????
		ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());

	if (ScreenPosition == FVector2D::ZeroVector && !IsPositionOnScreen)
		return false;

	return ScreenPosition.X > (-1 * LookaheadSpawnDistance) && ScreenPosition.Y > (-1 * LookaheadSpawnDistance) && ScreenPosition.X < ViewportSize.X && ScreenPosition.Y < ViewportSize.Y;
}

// Called every frame
void AAsteroidManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AccumulatedDeltaTime += DeltaTime;

	if (AccumulatedDeltaTime > RefreshFrequency)
	{
		AccumulatedDeltaTime = 0.0f;
		SpawnVisibleAsteroids();

		DespawnInvisibleAsteroids();
	}
}


float AAsteroidManager::RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

