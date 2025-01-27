// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStatisticsHUD.generated.h"

/**
 *
 */
UCLASS()
class MORTALIS_API UPlayerStatisticsHUD : public UUserWidget
{
    GENERATED_BODY()

public:
    void InitializeBindings();

    void SetHealth(float CurrentHealth, float MaxHealth);
    void SetMana(float CurrentMana, float MaxMana);

    UFUNCTION()
    void SetExperience(float CurrentExperience, float MaxExperience);

public:
    UPROPERTY(EditAnywhere, meta = (BindWidget))
    class UProgressBar *HealthBar;

    UPROPERTY(EditAnywhere, meta = (BindWidget))
    class UProgressBar *ManaBar;

    UPROPERTY(EditAnywhere, meta = (BindWidget))
    class UProgressBar *ExperienceBar;
};
