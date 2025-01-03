// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerStatisticsHUD.h"

#include "Components/ProgressBar.h"

void UPlayerStatisticsHUD::SetHealth(const float CurrentHealth, const float MaxHealth)
{
    if (HealthBar)
    {
        HealthBar->SetPercent(CurrentHealth / MaxHealth);
    }
}

void UPlayerStatisticsHUD::SetMana(const float CurrentMana, const float MaxMana)
{
    if (ManaBar)
    {
        ManaBar->SetPercent(CurrentMana / MaxMana);
    }
}

void UPlayerStatisticsHUD::SetExperience(const float CurrentExperience, const float MaxExperience)
{
    if (ExperienceBar)
    {
        ExperienceBar->SetPercent(CurrentExperience / MaxExperience);
    }
}