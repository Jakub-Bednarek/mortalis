// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "UI/Menus/DifficultySelectionWidget.h"

#include "GameDifficultySelector.generated.h"

UENUM()
enum class GameDifficulty : uint8
{
	Easy UMETA(DisplayName = "Easy"),
	Medium UMETA(DisplayName = "Medium"),
	Hard UMETA(DisplayName = "Hard"),
};

UCLASS()
class MORTALIS_API AGameDifficultySelector : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameDifficultySelector();

	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// BLEH TODO: custom base class for button to add difficulty parameter to delegate
	UFUNCTION()
	void EasyDifficultySelect();
	
	UFUNCTION()
	void MediumDifficultySelect();
	
	UFUNCTION()
	void HardDifficultySelect();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UDifficultySelectionWidget> DifficultySelectionWidgetClass;

private:
	void LoadSelectedLevel(GameDifficulty SelectedDifficulty);

private:
	UDifficultySelectionWidget* DifficultySelectionWidget;
};
