// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/GameFinishedMenu.h"

void UGameFinishedMenu::SetScore(int32 Score)
{
    ScoreValue->SetText(FText::FromString(FString::FromInt(Score)));
}