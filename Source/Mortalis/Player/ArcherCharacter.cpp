// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherCharacter.h"
#include "Projectiles/BasicProjectile.h"

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
	auto TargetLocation = GetActorLocation() + FVector(350.0f, 0.0f, 0.0f);
	auto* SpawnedProjectile = (ABasicProjectile*)GetWorld()->SpawnActor<AActor>(NormalProjectile, TargetLocation, FRotator(0.0f));

	SpawnedProjectile->Fire(FVector(1.0f, 0.0f, 0.0f));
}

void AArcherCharacter::SpecialAttack()
{
	auto TargetLocation = GetActorLocation() + FVector(350.0f, 0.0f, 0.0f);
	auto* SpawnedProjectile = (ABasicProjectile*)GetWorld()->SpawnActor<AActor>(SpecialProjectile, TargetLocation, FRotator(0.0f));

	SpawnedProjectile->Fire(FVector(1.0f, 0.0f, 0.0f));
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

