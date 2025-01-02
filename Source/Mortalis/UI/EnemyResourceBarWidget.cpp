// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyResourceBarWidget.h"

#include "Components/ProgressBar.h"

void UEnemyResourceBarWidget::SetResourcePercentage(const float Percent)
{
    if (ResourceProgressBar)
    {
        ResourceProgressBar->SetPercent(Percent);
    }
}

void UEnemyResourceBarWidget::SetResourcePercentage(const float CurrentValue, const float MaxValue)
{
    if (ResourceProgressBar)
    {
        ResourceProgressBar->SetPercent(CurrentValue / MaxValue);
    }
}