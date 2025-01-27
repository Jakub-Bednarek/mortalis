// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"

#include "UpgradeSelectionCard.generated.h"

/**
 *
 */
UCLASS()
class MORTALIS_API UUpgradeSelectionCard : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetName(FText Value);
    void SetDescription(FText Value);

public:
    UPROPERTY(EditAnywhere, meta = (BindWidget))
    class UTextBlock *Name;

    UPROPERTY(EditAnywhere, meta = (BindWidget))
    class UTextBlock *Description;

    UPROPERTY(EditAnywhere, meta = (BindWidget))
    UButton *CardButton;
};
