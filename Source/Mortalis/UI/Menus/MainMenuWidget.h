// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class MORTALIS_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* StartGameButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* SettingsButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* ExitButton;
};
