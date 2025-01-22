// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFinishedMenu.generated.h"

/**
 * 
 */
UCLASS()
class MORTALIS_API UGameFinishedMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetScore(int32 Score);

public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* ContinueButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* RestartButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* ScoreText;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock* ScoreValue;
};
