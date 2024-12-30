// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ArcherCharacter.generated.h"

UCLASS()
class MORTALIS_API AArcherCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AArcherCharacter();

	UFUNCTION(BlueprintCallable, category="Player/Movement")
	void MoveForward();

	UFUNCTION(BlueprintCallable, category="Player/Movement")
	void MoveBackward();

	UFUNCTION(BlueprintCallable, category="Player/Movement")
	void MoveLeft();

	UFUNCTION(BlueprintCallable, category="Player/Movement")
	void MoveRight();

	UFUNCTION(BlueprintCallable, category="Player/Attack")
	void NormalAttack();
	
	UFUNCTION(BlueprintCallable, category="Player/Attack")
	void SpecialAttack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void ProcessFrameMovement(float DeltaTime);

private:
	FVector FrameMovementVector = {0.0, 0.0, 0.0};

	double MovementSpeed = 400.0;
};
