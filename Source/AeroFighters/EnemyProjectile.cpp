// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyProjectile.h"
#include "Engine.h"
#include "PlayerMissile.h"
#include "PlayerLaser.h"
#include "Components/CapsuleComponent.h"
#include "PlayerCharacter.h"

// Sets default values
AEnemyProjectile::AEnemyProjectile() : Super()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	auto CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->InitCapsuleSize(5.f, 5.f);
	CapsuleComponent->SetCollisionProfileName(TEXT("Trigger"));
	CapsuleComponent->SetupAttachment(RootComponent);
	OnActorHit.AddDynamic(this, &AEnemyProjectile::OnHit);
}

// Called when the game starts or when spawned
void AEnemyProjectile::BeginPlay()
{
	Super::BeginPlay();

	// Bind an action to destroy the projectile if the character spawns a bomb
	// The action is a lambda function that destroys the projectile
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetCharacter());
	if (PlayerCharacter != nullptr)
	{
		PlayerCharacter->myDiscardEnemyShootsDelegate.AddDynamic(this, &AEnemyProjectile::OnBomb);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, FString(TEXT("[EnemyProjectile.cpp] - PlayerCharacter is nullptr")));
	}
}

void AEnemyProjectile::OnBomb()
{
	this->Destroy();
}

// Called every frame
void AEnemyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check if the projectile has to be destroyed
	if (StaticMesh->GetComponentLocation().X < BottomMovableArea->GetActorLocation().X)
	{
		this->Destroy();
	}

	// The basic movement (falling) is the same for all enemy projectile types
	FVector NewLocation = StaticMesh->GetComponentLocation() + (StaticMesh->GetForwardVector() * GetSpeed() * DeltaTime);
	StaticMesh->SetWorldLocation(NewLocation);
	//StaticMesh->SetWorldRotation(FRotator(90.f, 0.f, 0.f));
}

void AEnemyProjectile::OnHit(AActor* self, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		if (OtherActor->GetClass()->IsChildOf(APlayerLaser::StaticClass()))
		{
			this->Destroy();
		}
	}
}


