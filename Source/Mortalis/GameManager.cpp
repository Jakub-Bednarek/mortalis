// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include "Components/SlateWrapperTypes.h"
#include "Layout/Visibility.h"
#include "UI/Menus/GameFinishedMenu.h"

// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	
	GameFinishedMenu = (UGameFinishedMenu*)(CreateWidget(GetWorld(), GameFinishedMenuClass));
	GameFinishedMenu->AddToPlayerScreen();
	GameFinishedMenu->RestartButton->OnClicked.AddDynamic(this, &AGameManager::RestartGame);
	GameFinishedMenu->ContinueButton->OnClicked.AddDynamic(this, &AGameManager::ExitToMainMenu);

	HideLevelFinishedMenu();
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (not GameStateManager::Get().IsStateChanged())
	{
		return;
	}

	auto NewState = GameStateManager::Get().ConsumeStateChange();
	PropagateStateChangedEvent(NewState);
}

void AGameManager::PropagateStateChangedEvent(const EMortalisGameState NewState)
{
	switch (NewState)
	{
		case EMortalisGameState::LevelFinished:
		{
			if (OnLevelFinishedEvent.IsBound())
			{
				OnLevelFinishedEvent.Broadcast();
			}
			break;
		}
		case EMortalisGameState::Restarting:
		{
			if (OnLevelFinishedEvent.IsBound())
			{
				OnLevelFinishedEvent.Broadcast();
			}
			break;
		}
		case EMortalisGameState::PlayerDead:
		{
			if (OnPlayerDeathEvent.IsBound())
			{
				OnPlayerDeathEvent.Broadcast();
			}
			ShowLevelFinishedMenu();
			break;
		}
		default:
			break;
	}
}

void AGameManager::ShowLevelFinishedMenu()
{
	if (GameFinishedMenu)
	{
		GameFinishedMenu->SetVisibility(ESlateVisibility::Visible);
	}
}

void AGameManager::HideLevelFinishedMenu()
{
	if (GameFinishedMenu)
	{
		GameFinishedMenu->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AGameManager::RestartGame()
{
	UE_LOG(LogTemp, Log, TEXT("Restarting game..."));
}

void AGameManager::ExitToMainMenu()
{
	UE_LOG(LogTemp, Log, TEXT("Exitting to main menu..."));
}