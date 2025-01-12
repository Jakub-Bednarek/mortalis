// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UI/Components/UpgradeSelectionCard.h"

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

	UFUNCTION()
	void InitializeBindings();

public:
	UPROPERTY()
	FOnOptionSelected OnOptionSelectedEvent;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UUpgradeSelectionCard* FirstOption;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UUpgradeSelectionCard* SecondOption;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UUpgradeSelectionCard* ThirdOption;

private:
	void OnOptionSelected(FUpgradeIndex Index, EUpgradeCategory Category);

	UFUNCTION()
	void OnFirstOptionSelected();

	UFUNCTION()
	void OnSecondOptionSelected();

	UFUNCTION()
	void OnThirdOptionSelected();
private:
	TArray<FUpgradeUIData> UIData;
};
