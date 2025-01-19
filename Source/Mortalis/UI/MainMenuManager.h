// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UI/Menus/MainMenuWidget.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainMenuManager.generated.h"

UCLASS()
class MORTALIS_API AMainMenuManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMainMenuManager();

	virtual void Tick(float DeltaTime) override;

public:	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UMainMenuWidget> MainMenuWidgetClass;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void StartGame();

	UFUNCTION()
	void Exit();
private:
	TObjectPtr<UMainMenuWidget> MainMenuWidget;
};
