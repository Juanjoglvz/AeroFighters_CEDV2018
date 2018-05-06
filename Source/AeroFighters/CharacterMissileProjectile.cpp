// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterMissileProjectile.h"
#include "Engine.h"

// Sets default values
ACharacterMissileProjectile::ACharacterMissileProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Get StaticMesh associated with this projectile 
	auto StaticMeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Assets/Projectile/BasicMissile.BasicMissile'"));

	if (StaticMeshAsset.Succeeded())
		SetStaticMeshAsset(StaticMeshAsset.Object);

	SetSpeed(3.f);
}

// Called when the game starts or when spawned
void ACharacterMissileProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	// Resize projectile
	StaticMesh->SetWorldScale3D(FVector(5.f, 5.f, 5.f));
	StaticMesh->SetRelativeScale3D(FVector(5.f, 5.f, 5.f));

	// When a character's bomb is spawned, all EnemyProjectile are destroyed

}

// Called every frame
void ACharacterMissileProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACharacterMissileProjectile::Clone()
{

}

void ACharacterMissileProjectile::ProjectileBehaviour(float DeltaTime)
{

}
