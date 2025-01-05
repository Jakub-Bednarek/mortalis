// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "UI/Game/PlayerStatisticsHUD.h"

#include "ArcherCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyHit, float, Damage);

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

	UFUNCTION(BlueprintCallable, category="Player/Statistics")
	void AddExperience(float Value);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Projectiles")
	TSubclassOf<AActor> NormalProjectile {};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Projectiles")
	TSubclassOf<AActor> SpecialProjectile {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UPlayerStatisticsHUD> PlayerStatisticsHUDClass;

	// Delegates
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnEnemyHit OnEnemyHit;

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

	void UpdateExperienceHUD();
	void LevelUpCharacter();

private:
	FVector FrameMovementVector = {0.0, 0.0, 0.0};

	double MovementSpeed = 400.0;

	int32 CurrentLevel = 1;
	float ExperienceForNextLevel = 100.0f;
	float CurrentExperience = 0.0f;

	FVector ViewportCenter;
};
