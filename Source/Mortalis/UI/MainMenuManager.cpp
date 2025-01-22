// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenuManager.h"
#include "Components/SlateWrapperTypes.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMainMenuManager::AMainMenuManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMainMenuManager::BeginPlay()
{
	Super::BeginPlay();

	if (not MainMenuWidgetClass)
	{
		UE_LOG(LogTemp, Log, TEXT("Main menu widget class not set."));
		return;
	}	

	MainMenuWidget = (UMainMenuWidget*)(CreateWidget(GetWorld(), MainMenuWidgetClass));

	MainMenuWidget->StartGameButton->OnClicked.AddDynamic(this, &AMainMenuManager::StartGame);
	MainMenuWidget->ExitButton->OnClicked.AddDynamic(this, &AMainMenuManager::Exit);
	
	MainMenuWidget->AddToPlayerScreen();
	MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
}

// Called every frame
void AMainMenuManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMainMenuManager::StartGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), "SubLevelsTestMain");
}

void AMainMenuManager::Exit()
{
	FGenericPlatformMisc::RequestExit(false);
}