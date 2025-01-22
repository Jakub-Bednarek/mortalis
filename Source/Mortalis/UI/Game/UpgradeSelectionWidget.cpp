// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Game/UpgradeSelectionWidget.h"
#include "Misc/AssertionMacros.h"

// This approach is pretty bad, changing number of upgrades completely destroys the concept
// As we can't dynamically add function, need to find another way to carry index based on the button clicked
void UUpgradeSelectionWidget::InitializeBindings()
{
    FirstOption->CardButton->OnClicked.AddDynamic(this, &UUpgradeSelectionWidget::OnFirstOptionSelected);
    SecondOption->CardButton->OnClicked.AddDynamic(this, &UUpgradeSelectionWidget::OnSecondOptionSelected);
    ThirdOption->CardButton->OnClicked.AddDynamic(this, &UUpgradeSelectionWidget::OnThirdOptionSelected);
}

void UUpgradeSelectionWidget::ShowSelectionMenu(TArray<FUpgradeUIData> UpgradeChoices)
{
    check(UpgradeChoices.Num() == 3);
    UIData = MoveTemp(UpgradeChoices);

    FirstOption->SetName(FText::FromName(UIData[0].Name));
    FirstOption->SetDescription(FText::FromName(UIData[0].Description));
    
    SecondOption->SetName(FText::FromName(UIData[1].Name));
    SecondOption->SetDescription(FText::FromName(UIData[1].Description));
    
    ThirdOption->SetName(FText::FromName(UIData[2].Name));
    ThirdOption->SetDescription(FText::FromName(UIData[2].Description));

	SetVisibility(ESlateVisibility::Visible);
}

void UUpgradeSelectionWidget::HideSelectionMenu()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UUpgradeSelectionWidget::OnFirstOptionSelected()
{
    OnOptionSelected(UIData[0].Index, UIData[0].Category);
}

void UUpgradeSelectionWidget::OnSecondOptionSelected()
{
    OnOptionSelected(UIData[1].Index, UIData[1].Category);
}

void UUpgradeSelectionWidget::OnThirdOptionSelected()
{
    OnOptionSelected(UIData[2].Index, UIData[2].Category);
}

void UUpgradeSelectionWidget::OnOptionSelected(FUpgradeIndex Index, EUpgradeCategory Category)
{
	OnOptionSelectedEvent.ExecuteIfBound(Index, Category);
}