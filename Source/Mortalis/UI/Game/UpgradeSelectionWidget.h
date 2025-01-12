// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Systems/UpgradesSystem/Upgrades/UpgradeUIData.h"
#include "GameFramework/Types/UpgradeIndex.h"
#include "GameFramework/Types/UpgradeCategory.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UpgradeSelectionWidget.generated.h"

/**
 * 
 */

class UButton;

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnOptionSelected, FUpgradeIndex, Index, EUpgradeCategory, Category);

UCLASS()
class MORTALIS_API UUpgradeSelectionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void ShowSelectionMenu(TArray<FUpgradeUIData> UpgradeChoices);

	UFUNCTION()
	void HideSelectionMenu();

public:
	UPROPERTY()
	FOnOptionSelected OnOptionSelectedEvent;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* FirstOption;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* SecondOption;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* ThirdOption;

private:
	void OnOptionSelectedRun(uint8 OptionIndex);
};
