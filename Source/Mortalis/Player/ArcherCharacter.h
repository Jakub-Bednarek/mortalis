// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "UI/Game/PlayerStatisticsHUD.h"

#include "GameFramework/PlayerComponents/PlayerStatisticsComponent.h"
#include "GameFramework/PlayerComponents/NormalAttackComponent.h"
#include "GameFramework/PlayerComponents/SpecialAttackComponent.h"

#include "GameFramework/Systems/UpgradesSystem/Upgrades/StatisticsComponentUpgrade.h"

#include "ArcherCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyHit, float, Damage);

UCLASS()
class MORTALIS_API AArcherCharacter : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    AArcherCharacter();

    UFUNCTION(BlueprintCallable, category = "Player/Movement")
    void MoveForward();

    UFUNCTION(BlueprintCallable, category = "Player/Movement")
    void MoveBackward();

    UFUNCTION(BlueprintCallable, category = "Player/Movement")
    void MoveLeft();

    UFUNCTION(BlueprintCallable, category = "Player/Movement")
    void MoveRight();

    UFUNCTION(BlueprintCallable, category = "Player/Statistics")
    void AddExperience(float Value);

    UFUNCTION(BlueprintCallable, category = "Player")
    void HandlePlayerDeath();

    UFUNCTION(BlueprintCallable)
    bool IsMoving() const;

    UFUNCTION(BlueprintCallable)
    FRotator GetCurrentDirectionRotation();

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UPlayerStatisticsHUD> PlayerStatisticsHUDClass;

    // Delegates
    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnEnemyHit OnEnemyHit;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPlayerStatisticsComponent *PlayerStatisticsComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UNormalAttackComponent *NormalAttackComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USpecialAttackComponent *SpecialAttackComponent;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

private:
    UFUNCTION()
    void ProcessStatisticsUpgrade(UStatisticsComponentUpgrade *Upgrade);

    void ProcessFrameMovement(float DeltaTime);
    void UpdateExperienceHUD();
    void LevelUpCharacter();

private:
    FVector FrameMovementVector = {0.0, 0.0, 0.0};

    int32 CurrentLevel = 1;
    float ExperienceForNextLevel = 100.0f;
    float CurrentExperience = 0.0f;

    bool bIsDead = false;
    bool bIsMoving = false;

    FVector ViewportCenter;
};
