// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Components/UpgradeSelectionCard.h"

#include "Components/TextBlock.h"

void UUpgradeSelectionCard::SetName(FText Value)
{
    Name->SetText(Value);
}

void UUpgradeSelectionCard::SetDescription(FText Value)
{
    Description->SetText(Value);
}