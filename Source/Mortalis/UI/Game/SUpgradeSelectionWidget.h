// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widgets/Input/SButton.h"
#include "CoreMinimal.h"

#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class MORTALIS_API SUpgradeSelectionWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SUpgradeSelectionWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	UFUNCTION()
	void OnOptionSelected();

	UFUNCTION()
	void ShowSelectionMenu(TArray<FText> UpgradeOptions);

	UFUNCTION()
	void HideSelectionMenu();

	UFUNCTION()
	FText GetFirstOptionName() const;

	UFUNCTION()
	FText GetSecondOptionName() const;

	UFUNCTION()
	FText GetThirdOptionName() const;

private:
	void FillArrayWithDummyData();

private:
	TArray<FText> OptionNamesToSelect;
};
