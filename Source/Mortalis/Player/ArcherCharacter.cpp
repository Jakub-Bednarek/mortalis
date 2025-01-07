// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherCharacter.h"
#include "GameFramework/PlayerComponents/NormalAttackComponent.h"
#include "GameFramework/PlayerComponents/PlayerStatisticsComponent.h"
#include "GameFramework/PlayerComponents/SpecialAttackComponent.h"
#include "Logging/LogMacros.h"
#include "Projectiles/BasicProjectile.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"

#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

// Sets default values
AArcherCharacter::AArcherCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerStatisticsComponent = CreateDefaultSubobject<UPlayerStatisticsComponent>(TEXT("Statistics Component"));
	NormalAttackComponent = CreateDefaultSubobject<UNormalAttackComponent>(TEXT("Normal attack Component"));
	SpecialAttackComponent = CreateDefaultSubobject<USpecialAttackComponent>(TEXT("Special attack Component"));
}

// Called when the game starts or when spawned
void AArcherCharacter::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> UpgradesSystemActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Upgrades System"), UpgradesSystemActors);

	if (UpgradesSystemActors.Num() > 1 or UpgradesSystemActors.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("More than 1 or 0 actor with Upgrades System tag"));
		return;
	}

	AUpgradesSystem* UpgradesSystem = (AUpgradesSystem*)(UpgradesSystemActors[0]);
	if (UpgradesSystem != nullptr)
	{
		UpgradesSystem->OnUpgradeGenerated.AddDynamic(this, &AArcherCharacter::ConsumeUpgrade);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to bind to UpgradesSystem::OnUpgradeGEnerated delegate."));
	}
}

// Called every frame
void AArcherCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ProcessFrameMovement(DeltaTime);
}

void AArcherCharacter::MoveForward()
{
	// FrameMovementVector.Y += 1.0;
	FrameMovementVector.X += 1.0;
}

void AArcherCharacter::MoveBackward()
{
	FrameMovementVector.X -= 1.0;
}

void AArcherCharacter::MoveLeft()
{
	FrameMovementVector.Y -= 1.0;
}

void AArcherCharacter::MoveRight()
{
	FrameMovementVector.Y += 1.0;
}

void AArcherCharacter::AddExperience(float Value)
{
	CurrentExperience += Value;
	// PlayerStatisticsHUD->SetExperience(CurrentExperience, ExperienceForNextLevel);

	if (CurrentExperience >= ExperienceForNextLevel)
	{
		LevelUpCharacter();
	}
}

void AArcherCharacter::LevelUpCharacter()
{
	CurrentExperience -= ExperienceForNextLevel;
	ExperienceForNextLevel *= 1.1f;
	CurrentLevel += 1;

	UpdateExperienceHUD();
}

void AArcherCharacter::UpdateExperienceHUD()
{
	// PlayerStatisticsHUD->SetExperience(CurrentExperience, ExperienceForNextLevel);
}

void AArcherCharacter::ConsumeUpgrade(UUpgrade* Upgrade)
{
	UE_LOG(LogTemp, Log, TEXT("We drippin' biatch"));
}

void AArcherCharacter::ProcessFrameMovement(const float DeltaTime)
{
	if (FrameMovementVector == FVector(0.0))
	{
		return;
	}

	auto CharacterFrameStartLocation = GetActorLocation();

	FrameMovementVector.Normalize();
	FrameMovementVector *= DeltaTime;
	FrameMovementVector *= MovementSpeed;

	SetActorLocation(CharacterFrameStartLocation + FrameMovementVector);

	FrameMovementVector = FVector(0.0);
}

// Called to bind functionality to input
void AArcherCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

