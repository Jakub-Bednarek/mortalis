// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "UI/Game/PlayerStatisticsHUD.h"

#include "ArcherCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterLevelUp, int32, Level);

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
	UPROPERTY(BLueprintCallable, BlueprintAssignable)
	FOnCharacterLevelUp OnCharacterLevelUp;

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

	void StartNormalAttackTimer();
	void UpdateNormalAttackTimer(float DeltaTime);

	// Update each second instead of tick? - may be bad for mana regen
	void ApplyHealthRegeneration(float DeltaTime);
	void ApplyManaRegeneration(float DeltaTime);

	void UpdateExperienceHUD();
	void LevelUpCharacter();

	FVector CalculateAttackDirection() const;
private:
	FVector FrameMovementVector = {0.0, 0.0, 0.0};

	double MovementSpeed = 400.0;
	double AttacksPerSecond = 2.0;

	double MaxHealth = 100.0;
	double CurrentHealth = MaxHealth;
	double HealthRegenerationPerSecond = 0.2;

	double MaxMana = 50.0;
	double CurrentMana = MaxMana;
	double ManaRegenerationPerSecond = 10.0;
	double SpecialAttackManaCost = 50.0;

	int32 CurrentLevel = 1;
	float ExperienceForNextLevel = 100.0f;
	float CurrentExperience = 0.0f;
	
	UPlayerStatisticsHUD* PlayerStatisticsHUD;

	FVector ViewportCenter;

	// Normal attack
	float NormalAttackTimer = 0.0f;
	bool bCanExecuteNormalAttack = true;
};
