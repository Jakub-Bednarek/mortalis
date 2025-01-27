// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "ExperienceSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterLevelUp, uint32, Level);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnExperienceGained, float, CurrentExperience, float, MaxExperience);

UCLASS(BlueprintType)
class MORTALIS_API AExperienceSystem : public AActor
{
    GENERATED_BODY()

public:
    AExperienceSystem();

    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable)
    void AddExperience(float Experience);

    UFUNCTION()
    int32 GetMonstersKilled() const;

public:
    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnCharacterLevelUp OnCharacterLevelUp;

    UPROPERTY()
    FOnExperienceGained OnExperienceGainedEvent;

protected:
    virtual void BeginPlay() override;

private:
    bool CanLevelUp() const;

    void LevelUp();

private:
    // this part could make use of some strategy pattern
    int32 CurrentLevel = 0;

    float CurrentExperience = 0;
    float ExperienceForNextLevel = 100;

    int32 MonstersKilled = 0;
};
