// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherCharacter.h"

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
	UE_LOG(LogTemp, Log, TEXT("NormalAttack()"));
}

void AArcherCharacter::SpecialAttack()
{
	UE_LOG(LogTemp, Log, TEXT("SpecialAttack()"));
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

