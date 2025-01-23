// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherCharacter.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/PlayerComponents/NormalAttackComponent.h"
#include "GameFramework/PlayerComponents/PlayerStatisticsComponent.h"
#include "GameFramework/PlayerComponents/SpecialAttackComponent.h"
#include "GameFramework/Systems/UpgradesSystem/UpgradesSystem.h"
#include "GameManager.h"
#include "Logging/LogMacros.h"
#include "Player/ArcherCharacter.h"
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

	TArray<AActor*> UpgradesSystemActors {};
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUpgradesSystem::StaticClass(), UpgradesSystemActors);

	if (UpgradesSystemActors.Num() != 1)
	{
		UE_LOG(LogTemp, Error, TEXT("Expected exactly one UpgradesSystem actor, found %d"), UpgradesSystemActors.Num());
	}
	else
	{
		AUpgradesSystem* UpgradesSystemActor = (AUpgradesSystem*)(UpgradesSystemActors[0]);
		UpgradesSystemActor->OnStatisticsComponentUpgradeSelected.AddDynamic(this, &AArcherCharacter::ProcessStatisticsUpgrade);
	}
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
		bIsMoving = false;
		return;
	}

	auto CharacterFrameStartLocation = GetActorLocation();

	FrameMovementVector.Normalize();
	FrameMovementVector *= DeltaTime;
	FrameMovementVector *= PlayerStatisticsComponent->GetMovementSpeed();

	SetActorLocation(CharacterFrameStartLocation + FrameMovementVector);
	bIsMoving = true;

	FrameMovementVector = FVector(0.0);
}

void AArcherCharacter::ProcessStatisticsUpgrade(UStatisticsComponentUpgrade* Upgrade)
{
	Upgrade->Apply(PlayerStatisticsComponent);
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

bool AArcherCharacter::IsMoving() const
{
	return bIsMoving;
}

FRotator AArcherCharacter::GetCurrentDirectionRotation()
{
	FHitResult Hit;
	bool bHitSuccessful = false;

	// Most likely inefficient
	auto* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	bHitSuccessful = PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	
	APawn* ControlledPawn = PlayerController->GetPawn();
	if (ControlledPawn != nullptr)
	{
		auto ResultDirection = (Hit.Location - GetActorLocation()).GetSafeNormal();
		return FVector(ResultDirection.X, ResultDirection.Y, 0.0f).Rotation();
	}

	return FVector().Rotation();
}