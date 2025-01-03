// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherCharacter.h"
#include "Projectiles/BasicProjectile.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"

#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

// Sets default values
AArcherCharacter::AArcherCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AArcherCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// TODO: this should definitely not be here + doesn't get updated on viewport resize!
	const auto ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	ViewportCenter = FVector(ViewportSize.X / 2.0f, ViewportSize.Y / 2.0f, 0.0f);

	PlayerStatisticsHUD = (UPlayerStatisticsHUD*)(CreateWidget(UGameplayStatics::GetPlayerController(GetWorld(), 0), PlayerStatisticsHUDClass));
	PlayerStatisticsHUD->AddToPlayerScreen();
}

// Called every frame
void AArcherCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ProcessFrameMovement(DeltaTime);

	if(not bCanExecuteNormalAttack)
	{
		UpdateNormalAttackTimer(DeltaTime);
	}

	ApplyHealthRegeneration(DeltaTime);
	ApplyManaRegeneration(DeltaTime);
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

void AArcherCharacter::NormalAttack()
{
	if (not bCanExecuteNormalAttack)
	{
		return;
	}

	const auto Direction = CalculateAttackDirection();
	auto TargetLocation = GetActorLocation() + (150.0f * Direction);
	auto* SpawnedProjectile = (ABasicProjectile*)GetWorld()->SpawnActor<AActor>(NormalProjectile, TargetLocation, FRotator(0.0f));

	if (IsValid(SpawnedProjectile))
	{
		SpawnedProjectile->Fire(Direction);
		StartNormalAttackTimer();
	}
}

void AArcherCharacter::SpecialAttack()
{
	if (not (CurrentMana >= SpecialAttackManaCost))
	{
		return;
	}

	CurrentMana -= SpecialAttackManaCost;

	const auto Direction = CalculateAttackDirection();
	auto TargetLocation = GetActorLocation() + (150.0f * Direction);
	auto* SpawnedProjectile = (ABasicProjectile*)GetWorld()->SpawnActor<AActor>(SpecialProjectile, TargetLocation, FRotator(0.0f));

	if (IsValid(SpawnedProjectile))
	{
		SpawnedProjectile->Fire(CalculateAttackDirection());
	}

	PlayerStatisticsHUD->SetMana(CurrentMana, MaxMana);
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

void AArcherCharacter::StartNormalAttackTimer()
{
	bCanExecuteNormalAttack = false;
	NormalAttackTimer = 0.0f;
}

void AArcherCharacter::UpdateNormalAttackTimer(float DeltaTime)
{
	NormalAttackTimer += DeltaTime;

	if (NormalAttackTimer >= (1.0 / AttacksPerSecond))
	{
		bCanExecuteNormalAttack = true;
	}
}

void AArcherCharacter::ApplyHealthRegeneration(float DeltaTime)
{
	PlayerStatisticsHUD->SetHealth(CurrentHealth, MaxHealth);
	if (CurrentHealth >= MaxHealth)
	{
		return;
	}

	CurrentHealth += HealthRegenerationPerSecond * DeltaTime;

	PlayerStatisticsHUD->SetHealth(CurrentHealth, MaxHealth);
}

void AArcherCharacter::ApplyManaRegeneration(float DeltaTime)
{
	PlayerStatisticsHUD->SetMana(CurrentMana, MaxMana);
	if (CurrentMana >= MaxMana)
	{
		return;
	}

	CurrentMana += ManaRegenerationPerSecond * DeltaTime;
	PlayerStatisticsHUD->SetMana(CurrentMana, MaxMana);
}

// TODO: when mouse is in the corner projectiles have slight offset but when on Axis they're perfectly fine
FVector AArcherCharacter::CalculateAttackDirection() const
{
	float MouseX;
	float MouseY;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(MouseX, MouseY);

	auto Direction = (ViewportCenter - FVector(MouseX, MouseY, 0.0f));
	Direction.Normalize();
	Direction = FVector(Direction.Y, -Direction.X, 0.0f); // Swap X and Y coordinates to align with world axis

	if (Direction.X == 0.0f and Direction.Y == 0.0f)
	{
		return FVector(0.5f, 0.5f, 0.0f);
	}

	return Direction;
}

// Called to bind functionality to input
void AArcherCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

