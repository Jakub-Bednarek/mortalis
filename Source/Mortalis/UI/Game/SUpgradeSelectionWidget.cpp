// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Game/SUpgradeSelectionWidget.h"
#include "Framework/SlateDelegates.h"
#include "Layout/Visibility.h"
#include "SUpgradeSelectionWidget.h"
#include "SlateOptMacros.h"
#include "Templates/SharedPointer.h"
#include "Types/SlateEnums.h"

#include "Engine/GameViewportClient.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

#include "Widgets/Input/SButton.h"
#include "Widgets/Layout/SUniformGridPanel.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SUpgradeSelectionWidget::Construct(const FArguments& InArgs)
{	
	FText Opt1 = NSLOCTEXT("UpgradeSelection", "Option1", "Option 1");
	FText Opt2 = NSLOCTEXT("UpgradeSelection", "Option2", "Option 2");
	FText Opt3 = NSLOCTEXT("UpgradeSelection", "Option3", "Option 3");

	FillArrayWithDummyData();

	auto Option1Button = SNew(SButton).OnClicked_Lambda([this]() { this->OnOptionSelected(); return FReply::Handled(); })[SNew(STextBlock).Text(this, &SUpgradeSelectionWidget::GetFirstOptionName)];
	auto Option2Button = SNew(SButton).OnClicked_Lambda([this]() { this->OnOptionSelected(); return FReply::Handled(); })[SNew(STextBlock).Text(this, &SUpgradeSelectionWidget::GetSecondOptionName)];
	auto Option3Button = SNew(SButton).OnClicked_Lambda([this]() { this->OnOptionSelected(); return FReply::Handled(); })[SNew(STextBlock).Text(this, &SUpgradeSelectionWidget::GetThirdOptionName)];

	ChildSlot
	[
		SNew(SUniformGridPanel)
		.SlotPadding(FMargin(100.0f, 100.0f))
		+SUniformGridPanel::Slot(0, 0)
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			Option1Button
		]
		+SUniformGridPanel::Slot(1, 0)
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			Option2Button
		]
		+SUniformGridPanel::Slot(2, 0)
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			Option3Button
		]
	];

	SetContentScale(TAttribute<FVector2D>(FVector2D(0.5f, 0.5f)));
	GEngine->GameViewport->AddViewportWidgetContent(SharedThis(this));

	SetVisibility(TAttribute<EVisibility>(EVisibility::Hidden));
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SUpgradeSelectionWidget::OnOptionSelected()
{
	if(OnOptionSelectedEvent.IsBound())
	{
		// TODO: Bad, should return ID of option selected
		OnOptionSelectedEvent.Broadcast(UpgradeChoice::First);
	}
}

FText SUpgradeSelectionWidget::GetFirstOptionName() const
{
	return OptionNamesToSelect[0];
}

FText SUpgradeSelectionWidget::GetSecondOptionName() const
{
	return OptionNamesToSelect[1];
}

FText SUpgradeSelectionWidget::GetThirdOptionName() const
{
	return OptionNamesToSelect[2];
}

void SUpgradeSelectionWidget::ShowSelectionMenu(TArray<FText> Value)
{
	OptionNamesToSelect = Value;
	SetVisibility(TAttribute<EVisibility>(EVisibility::Visible));
}

void SUpgradeSelectionWidget::HideSelectionMenu()
{
	SetVisibility(TAttribute<EVisibility>(EVisibility::Hidden));
}

void SUpgradeSelectionWidget::FillArrayWithDummyData()
{
	OptionNamesToSelect = TArray<FText>({NSLOCTEXT("Upgrades", "Dummy", "Dummy"), NSLOCTEXT("Upgrades", "Dummy", "Dummy"), NSLOCTEXT("Upgrades", "Dummy", "Dummy")});
}