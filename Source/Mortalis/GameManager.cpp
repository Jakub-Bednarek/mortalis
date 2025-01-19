// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

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
			break;
		}
		default:
			break;
	}
}
