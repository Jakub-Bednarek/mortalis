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
	
	// TODO: this should definitely not be here
	const auto ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	ViewportCenter = FVector(ViewportSize.X / 2.0f, ViewportSize.Y / 2.0f, 0.0f);
}

// Called every frame
void AArcherCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ProcessFrameMovement(DeltaTime);
}

void AArcherCharacter::MoveForward()
{
	FrameMovementVector.Y += 1.0;
	FrameMovementVector.X += 1.0;
}

void AArcherCharacter::MoveBackward()
{
	FrameMovementVector.Y -= 1.0;
	FrameMovementVector.X -= 1.0;
}

void AArcherCharacter::MoveLeft()
{
	FrameMovementVector.Y -= 1.0;
	FrameMovementVector.X += 1.0;
}

void AArcherCharacter::MoveRight()
{
	FrameMovementVector.Y += 1.0;
	FrameMovementVector.X -= 1.0;
}

void AArcherCharacter::NormalAttack()
{
	const auto Direction = CalculateAttackDirection();
	auto TargetLocation = GetActorLocation() + (150.0f * Direction);
	auto* SpawnedProjectile = (ABasicProjectile*)GetWorld()->SpawnActor<AActor>(NormalProjectile, TargetLocation, FRotator(0.0f));

	SpawnedProjectile->Fire(Direction);
}

void AArcherCharacter::SpecialAttack()
{
	const auto Direction = CalculateAttackDirection();
	auto TargetLocation = GetActorLocation() + (150.0f * Direction);
	auto* SpawnedProjectile = (ABasicProjectile*)GetWorld()->SpawnActor<AActor>(SpecialProjectile, TargetLocation, FRotator(0.0f));

	SpawnedProjectile->Fire(CalculateAttackDirection());
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

FVector AArcherCharacter::CalculateAttackDirection() const
{
	float MouseX;
	float MouseY;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(MouseX, MouseY);

	auto Direction = (ViewportCenter - FVector(MouseX, MouseY, 0.0f)).RotateAngleAxis(-45.0, FVector(0.0f, 0.0f, 1.0f));
	Direction.Normalize();

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

