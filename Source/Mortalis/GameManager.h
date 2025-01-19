// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnLevelFinished);
DECLARE_MULTICAST_DELEGATE(FOnLevelRestart);
DECLARE_MULTICAST_DELEGATE(FOnPlayerDeath);

UENUM()
enum class EMortalisGameState : uint8
{
	MainMenu UMETA(DisplayName="MainMenu"),
	LevelLoading UMETA(DisplayName="LevelLoading"),
	Playing UMETA(DisplayName="Playing"),
	Paused UMETA(DisplayName="Paused"),
	PlayerDead UMETA(DisplayName="PlayerDead"),
	LevelFinished UMETA(DisplayName="LevelFinished"),
	Restarting UMETA(DisplayName="Restarting")
};

UCLASS()
class MORTALIS_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameManager();
	
	virtual void Tick(float DeltaTime) override;

public:
	FOnLevelFinished OnLevelFinishedEvent;
	FOnLevelRestart OnLevelRestartEvent;
	FOnPlayerDeath OnPlayerDeathEvent;

protected:
	virtual void BeginPlay() override;

private:
	void PropagateStateChangedEvent(const EMortalisGameState NewState);
};

class GameStateManager
{
public:
	GameStateManager() : CurrentState(EMortalisGameState::MainMenu) {}

	static GameStateManager& Get()
	{
		static GameStateManager Instance {};

		return Instance;
	}

	void AddStateChange(const EMortalisGameState TargetState)
	{
		UE_LOG(LogTemp,
			Verbose,
			TEXT("State transition [%s] -> [%s]"),
			*UEnum::GetValueAsString(CurrentState),
			*UEnum::GetValueAsString(TargetState)
		);

		bStateChanged = true;
	}

	bool IsStateChanged() const
	{
		return bStateChanged;
	}

	EMortalisGameState ConsumeStateChange()
	{
		bStateChanged = false;

		return CurrentState;
	}
 
private:
	EMortalisGameState CurrentState;

	bool bStateChanged = false;
};