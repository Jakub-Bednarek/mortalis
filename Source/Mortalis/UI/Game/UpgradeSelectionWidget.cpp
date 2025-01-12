// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Game/UpgradeSelectionWidget.h"


void UUpgradeSelectionWidget::OnOptionSelectedRun(uint8 OptionIndex)
{
	OnOptionSelectedEvent.ExecuteIfBound(FUpgradeIndex { 0 }, EUpgradeCategory {});
}


void UUpgradeSelectionWidget::ShowSelectionMenu(TArray<FUpgradeUIData> UpgradeChoices)
{
	// OptionNamesToSelect = Value;
	SetVisibility(ESlateVisibility::Visible);
}

void UUpgradeSelectionWidget::HideSelectionMenu()
{
	SetVisibility(ESlateVisibility::Hidden);
}
