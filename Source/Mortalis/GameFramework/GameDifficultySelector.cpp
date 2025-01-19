// Fill out your copyright notice in the Description page of Project Settings.


#include "GameDifficultySelector.h"
#include "GameManager.h"

#include "Engine/LatentActionManager.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ObjectMacros.h"

// Sets default values
AGameDifficultySelector::AGameDifficultySelector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameDifficultySelector::BeginPlay()
{
	Super::BeginPlay();
	
	DifficultySelectionWidget = (UDifficultySelectionWidget*)(CreateWidget(GetWorld(), DifficultySelectionWidgetClass));
	DifficultySelectionWidget->AddToPlayerScreen();

	DifficultySelectionWidget->EasyDifficultyButton->OnClicked.AddUniqueDynamic(this, &AGameDifficultySelector::EasyDifficultySelect);
	DifficultySelectionWidget->MediumDifficultyButton->OnClicked.AddUniqueDynamic(this, &AGameDifficultySelector::MediumDifficultySelect);
	DifficultySelectionWidget->HardDifficultyButton->OnClicked.AddUniqueDynamic(this, &AGameDifficultySelector::HardDifficultySelect);
}

// Called every frame
void AGameDifficultySelector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameDifficultySelector::EasyDifficultySelect()
{
	LoadSelectedLevel(GameDifficulty::Easy);
}

void AGameDifficultySelector::MediumDifficultySelect()
{
	LoadSelectedLevel(GameDifficulty::Easy);
}

void AGameDifficultySelector::HardDifficultySelect()
{
	LoadSelectedLevel(GameDifficulty::Easy);
}

void AGameDifficultySelector::LoadSelectedLevel(GameDifficulty SelectedDifficulty)
{
	GameStateManager::Get().AddStateChange(EMortalisGameState::LevelLoading);
	UGameplayStatics::OpenLevel(GetWorld(), "SubLevelsTestMain");
	GameStateManager::Get().AddStateChange(EMortalisGameState::Playing);
}