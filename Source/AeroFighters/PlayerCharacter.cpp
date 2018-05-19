// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "PlayerLaser.h"
#include "EnemyProjectile.h"
#include "PlayerMissile.h"
#include "RecordsManager.h"
#include "Blueprint/UserWidget.h"
#include "TextWidgetTypes.h"
#include "TextBlock.h"
#include "Engine.h"


// Sets default values

APlayerCharacter::APlayerCharacter() : 
	NumberOfBombsAvailable{ 3 }, NumberOfLives{ 5 }, MoveSpeed { 1000.f }, CameraSpeed{ 150.f, 0.f, 0.f }, 
	b_IsShooting{ false }, Timer{ 0.25f }, ShootTimer{ 0.25f }, MissileTimer{ 0.f }, MissileMaxTime{ 1.f },
    CurrentPower{ PlayerPower::BasicShot}, b_IsVulnerable{ true }, MaximumVulnerabilityTime{ 3.f }, b_IsFlashing { false },
    VulnerableTimer{ 0.f }, ShowAndHideTimer{ 0.f }, MaxNumberOfBombs(5), PostProcessingTimer { 0.f }, FlashTime { 0.75f }
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	
	//Set Static Mesh
	auto StaticMeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Assets/Ships/Plane'"));

	if (StaticMeshAsset.Succeeded()) {
		StaticMeshComponent->SetStaticMesh(StaticMeshAsset.Object);
		StaticMeshComponent->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
		StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	}
	
	// Set shooting audio
	static ConstructorHelpers::FObjectFinder<USoundCue> soundCue(TEXT("SoundCue'/Game/Sounds/Shoot_Cue.Shoot_Cue'"));
	shootingAudioCue = soundCue.Object;

	shootingAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	shootingAudioComponent->bAutoActivate = false;
	shootingAudioComponent->AttachTo(RootComponent);
	
	if (shootingAudioCue->IsValidLowLevelFast()) {
		shootingAudioComponent->SetSound(shootingAudioCue);
	}

	//Take control of player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Add OnHit function to OnActorHit event
	GetCapsuleComponent()->bGenerateOverlapEvents = true;
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("OverlapAll"));
}

void APlayerCharacter::IncreaseBombs()
{
	if (NumberOfBombsAvailable < MaxNumberOfBombs)
		NumberOfBombsAvailable++;
	else if (RecordsManagerReference.IsValid()) // Increase Score
		RecordsManagerReference.Get()->MyIncreaseScore.ExecuteIfBound(1000);
}

void APlayerCharacter::IncreasePower()
{
	switch (CurrentPower)
	{
		case PlayerPower::BasicShot:
			CurrentPower = PlayerPower::WideShot;
			break;
		case PlayerPower::WideShot:
			CurrentPower = PlayerPower::WideShotMissile;
			break;
		case PlayerPower::WideShotMissile:
			CurrentPower = PlayerPower::FullPower;
			break;
		case PlayerPower::FullPower:
			if (RecordsManagerReference.IsValid())
				RecordsManagerReference.Get()->MyIncreaseScore.ExecuteIfBound(1000);
			break;
	}
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Get reference to RecordManager
	FString RecordsManagerString = FString(TEXT("RecordsManager"));

	// Get PostProcess component
	TArray<UPostProcessComponent*> Comps;
	GetComponents(Comps);
	if (Comps.Num() > 0)
	{
		PostProcessComponent = Comps[0];
	}
	PostProcessComponent->BlendWeight = 0.f;

	//Get The references to the borders
	FString TopMovableAreaString = FString(TEXT("TopMovableArea"));
	FString BottomMovableAreaString = FString(TEXT("BottomMovableArea"));
	FString RightMovableAreaString = FString(TEXT("RightMovableArea"));
	FString LeftMovableAreaString = FString(TEXT("LeftMovableArea"));
	uint32 i = 0;
	for (TActorIterator<AActor> itr(GetWorld()); itr; ++itr)
	{
		// References to borders
		if (TopMovableAreaString.Equals(itr->GetName()))
		{
			this->TopMovableArea = *itr;
			i++;
		}
		else if (BottomMovableAreaString.Equals(itr->GetName()))
		{
			this->BottomMovableArea = *itr;
			i++;
		}
		else if (RightMovableAreaString.Equals(itr->GetName()))
		{
			this->RightMovableArea = *itr;
			i++;
		}
		else if (LeftMovableAreaString.Equals(itr->GetName()))
		{
			this->LeftMovableArea = *itr;
			i++;
		}

		// Get RecordsManager reference
		if (itr->GetName().Contains(RecordsManagerString))
		{
			RecordsManagerReference = Cast<ARecordsManager>(*itr);
			i++;
		}

		if (i > 4)
		{
			break;
		}
	}

	// Set HUD text for the number of available bombs
	// Create the Records Widget
	if (WBombs)
	{
		pWBomb = CreateWidget<UUserWidget>(GetGameInstance(), WBombs);
		if (pWBomb)
		{
			pWBomb->AddToViewport();
			pWBombText = (UTextBlock*)pWBomb->GetWidgetFromName("NumberOfBombs");
			pWHealthText = (UTextBlock*)pWBomb->GetWidgetFromName("Health");

			if (pWBombText != nullptr)
				pWBombText->SetText(FText::AsNumber(NumberOfBombsAvailable));

			if (pWHealthText != nullptr)
				pWHealthText->SetText(FText::AsNumber(NumberOfLives));
		}
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	VulnerableTimer += DeltaTime;
	ShowAndHideTimer += DeltaTime; 

	
	if (b_IsFlashing && PostProcessingTimer <= FlashTime)
	{
		PostProcessingTimer += DeltaTime;
	}
	else
	{
		b_IsFlashing = false;
		PostProcessingTimer = 0.f;
		PostProcessComponent->BlendWeight = 0.f;
	}

	//Move at the same rate as the camera
	FVector NewLocation = GetActorLocation();

	NewLocation += CameraSpeed * DeltaTime;
	FVector NewMovedLocationX = FVector(NewLocation.X, NewLocation.Y, NewLocation.Z);
	FVector NewMovedLocationY = FVector(NewLocation.X, NewLocation.Y, NewLocation.Z);

	//Handle movement based on our "MoveX" and "MoveY" axes
	if (!MovementInput.IsZero())
	{
		//Scale our movement input axis values by 1000 units per second
		MovementInput = MovementInput.GetSafeNormal() * MoveSpeed;
		NewMovedLocationX += GetActorForwardVector() * MovementInput.X * DeltaTime;
		if (IsPosMoveX(NewMovedLocationX))
		{
			NewLocation.X = NewMovedLocationX.X;
		}
		NewMovedLocationY += GetActorRightVector() * MovementInput.Y * DeltaTime;
		if (IsPosMoveY(NewMovedLocationY))
		{
			NewLocation.Y = NewMovedLocationY.Y;
		}
	}

	SetActorLocation(NewLocation);

	Shoot(DeltaTime);

	// Check if player is invulnerable. If it is, show and hide StaticMesh
	if (!b_IsVulnerable && VulnerableTimer <= MaximumVulnerabilityTime)
	{
		if (ShowAndHideTimer > 0.3f)
		{
			StaticMeshComponent->SetHiddenInGame(!StaticMeshComponent->bHiddenInGame);
			ShowAndHideTimer = 0.f;
		}
	}
	else 
	{
		b_IsVulnerable = true;

		// If mesh is hidden, show it
		if (StaticMeshComponent->bHiddenInGame)
			StaticMeshComponent->SetHiddenInGame(false);
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Bind Input functions
	InputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	InputComponent->BindAction("Bomb", IE_Pressed, this, &APlayerCharacter::ThrowABomb);
	InputComponent->BindAction("NormalShoot", IE_Pressed, this, &APlayerCharacter::Shoot);
	InputComponent->BindAction("NormalShoot", IE_Released, this, &APlayerCharacter::StopShooting);
}

void APlayerCharacter::MoveForward(float AxisValue)
{
	MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void APlayerCharacter::MoveRight(float AxisValue)
{
	MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

// If character throw a bomb, all enemy projectiles will be destroyed
void APlayerCharacter::ThrowABomb()
{
	b_IsFlashing = true;

	if (NumberOfBombsAvailable > 0)
	{
		myDiscardEnemyShootsDelegate.Broadcast();
		NumberOfBombsAvailable--;

		// Flash effect
		PostProcessComponent->BlendWeight = 1.f;
	}

	// Update number of bombs in the HUD
	if (pWBombText != nullptr)
		pWBombText->SetText(FText::AsNumber(NumberOfBombsAvailable));
}

void APlayerCharacter::Shoot()
{
	b_IsShooting = true;
}

void APlayerCharacter::StopShooting()
{
	b_IsShooting = false;
}

bool APlayerCharacter::IsPosMoveX(FVector NewPos) const
{
	//Check if possible to move in X axis
	if (NewPos.X >= this->BottomMovableArea->GetActorLocation().X && NewPos.X <= this->TopMovableArea->GetActorLocation().X)
	{
		return true;
	}

	return false;
}

bool APlayerCharacter::IsPosMoveY(FVector NewPos) const
{
	//Check if possible to move in Y axis
	if (NewPos.Y >= this->LeftMovableArea->GetActorLocation().Y && NewPos.Y <= this->RightMovableArea->GetActorLocation().Y)
	{
		return true;
	}

	return false;
}

void APlayerCharacter::Shoot(float DeltaTime)
{
	Timer += DeltaTime;
	MissileTimer += DeltaTime;

	// Check if player is shooting. If player is shooting, spawns projectiles.

	if (b_IsShooting && Timer > ShootTimer)
	{
		FRotator Rotation(0.f, 0.f, 0.f);
		FActorSpawnParameters SpawnInfo;
		if (CurrentPower == PlayerPower::BasicShot)
		{
			for (int i = -1; i <= 1; i++)
			{
				FVector Location = this->GetActorLocation();
				Location += FVector(10.f, i * 20.f, 0.f);
				if (i == 0)
				{
					Location += FVector(20.f, 0.f, 0.f);
				}

				GetWorld()->SpawnActor<APlayerLaser>(Location, Rotation, SpawnInfo);
				shootingAudioComponent->Play();
			}
			MissileTimer = 0.f;
		}
		else if (CurrentPower == PlayerPower::WideShot)
		{
			for (int i = -2; i <= 2; i++)
			{
				FVector Location = this->GetActorLocation();
				Location += FVector(10.f, i * 30.f, 0.f);
				if (i == 0)
				{
					Location += FVector(20.f, 0.f, 0.f);
				}
				GetWorld()->SpawnActor <APlayerLaser>(Location, Rotation, SpawnInfo);
				shootingAudioComponent->Play();
			}
			MissileTimer = 0.f;
		}
		else if (CurrentPower == PlayerPower::WideShotMissile)
		{
			for (int i = -2; i <= 2; i++)
			{
				FVector Location = this->GetActorLocation();
				Location += FVector(10.f, i * 30.f, 0.f);
				if (i == 0)
				{
					Location += FVector(20.f, 0.f, 0.f);
				}
				GetWorld()->SpawnActor<APlayerLaser>(Location, Rotation, SpawnInfo);
				shootingAudioComponent->Play();
			}
			if (MissileTimer > MissileMaxTime * 3)
			{
				for (int i = -1; i <= 1; i += 2)
				{
					GEngine->AddOnScreenDebugMessage(5, 5.f, FColor::Blue, FString(TEXT("Lanzando misil")));
					FVector Location = this->GetActorLocation();
					Location += FVector(-20.f, i * 40.f, 0.f);
					GetWorld()->SpawnActor<APlayerMissile>(Location, Rotation, SpawnInfo);
					shootingAudioComponent->Play();
				}
				MissileTimer = 0.f;
			}
		}
		else if (CurrentPower == PlayerPower::FullPower)
		{
			for (int i = -2; i <= 2; i++)
			{
				FVector Location = this->GetActorLocation();
				Location += FVector(10.f, i * 30.f, 0.f);
				if (i == 0)
				{
					Location += FVector(20.f, 0.f, 0.f);
				}
				GetWorld()->SpawnActor<APlayerLaser>(Location, Rotation, SpawnInfo);
				shootingAudioComponent->Play();
			}

			if (MissileTimer > MissileMaxTime * 2)
			{
				for (int i = -1; i <= 1; i++)
				{
					FVector Location = this->GetActorLocation();
					Location += FVector(-20.f, i * 40.f, 0.f);
					if (i == 0)
					{
						Location += FVector(-80.f, 0.f, 0.f);
					}
					GetWorld()->SpawnActor<APlayerMissile>(Location, Rotation, SpawnInfo);
					shootingAudioComponent->Play();
				}
				MissileTimer = 0.f;
			}

		}
		Timer = 0.f;
	}
}

void APlayerCharacter::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor)
{
	if (OtherActor)
	{
		if (OtherActor->GetClass()->IsChildOf(AEnemyProjectile::StaticClass()))
		{
			if (NumberOfLives > 0 && b_IsVulnerable)
			{
				NumberOfLives--;
				// Make player invulnerable
				b_IsVulnerable = false; 
				VulnerableTimer = 0.f;
				// Set Power State to 0
				this->CurrentPower = PlayerPower::BasicShot;
			}
			else if (NumberOfLives == 0 && b_IsVulnerable){
			    // Save the punctuation and go main menu
			    RecordsManagerReference->MyRecordsDelegate.ExecuteIfBound(); 
				OtherActor->Destroy();
				this->Destroy();
			    UGameplayStatics::OpenLevel(GetWorld(), FName("MainMenu"));
			}
			if (pWHealthText != nullptr)
				pWHealthText->SetText(FText::AsNumber(NumberOfLives));
		}
	}
}