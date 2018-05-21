/* Copyright (C) 2018 Iván García, Juan José Corroto and Javier Córdoba - All Rights Reserved
* You may use, distribute and modify this code under the
* terms of the GNU GPLv3 license.
*
* You should have received a copy of the GNU GPLv3 license with
* this file. If not, please write to: ivan.garcia16@alu.uclm.es
*/

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
	
	auto BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));

	BoxCollision->SetCollisionProfileName(TEXT("OverlapAll"));
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->bGenerateOverlapEvents = true;
	BoxCollision->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));
	BoxCollision->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	StaticMesh->SetupAttachment(RootComponent);

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyProjectile::OnOverlap);
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
	if (StaticMesh->GetComponentLocation().X < BottomMovableArea->GetActorLocation().X - 200.f 
		|| StaticMesh->GetComponentLocation().Y > RightMovableArea->GetActorLocation().Y + 300
		|| StaticMesh->GetComponentLocation().Y < LeftMovableArea->GetActorLocation().Y - 300)
	{
		this->Destroy();
	}
}

void AEnemyProjectile::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		if (OtherActor->GetClass()->IsChildOf(APlayerMissile::StaticClass()))
		{
			this->Destroy();
		}
	}
}


