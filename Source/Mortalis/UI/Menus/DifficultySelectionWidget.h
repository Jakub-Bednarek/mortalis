// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"

#include "DifficultySelectionWidget.generated.h"

/**
 * 
 */
UCLASS()
class MORTALIS_API UDifficultySelectionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* EasyDifficultyButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* MediumDifficultyButton;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* HardDifficultyButton; 
};
