// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherCharacter.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/PlayerComponents/NormalAttackComponent.h"
#include "GameFramework/PlayerComponents/PlayerStatisticsComponent.h"
#include "GameFramework/PlayerComponents/SpecialAttackComponent.h"
#include "GameManager.h"
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
	// SkillAttackComponent = CreateDefaultSubobject<USkillComponent>(TEXT("Skill Component"));
}

// Called when the game starts or when spawned
void AArcherCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AArcherCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsDead)
	{
		return;
	}

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

void AArcherCharacter::HandlePlayerDeath()
{
	bIsDead = true;
	SetActorEnableCollision(false);
	GameStateManager::Get().AddStateChange(EMortalisGameState::PlayerDead);
}