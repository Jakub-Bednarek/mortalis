// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyResourceBarWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class MORTALIS_API UEnemyResourceBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetResourcePercentage(float Percent);
	void SetResourcePercentage(float CurrentValue, float MaxValue);

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* ResourceProgressBar;
};
