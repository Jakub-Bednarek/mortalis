// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradesSystem.h"
#include "GameFramework/Systems/UpgradesSystem/UpgradesSystem.h"

// Sets default values
AUpgradesSystem::AUpgradesSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUpgradesSystem::BeginPlay()
{
	Super::BeginPlay();
	
	check(ExperienceSystem);

	ExperienceSystem->OnCharacterLevelUp.AddDynamic(this, &AUpgradesSystem::ProcessCharacterLevelUp);
}

// Called every frame
void AUpgradesSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUpgradesSystem::ProcessCharacterLevelUp(const uint32 Level)
{
	UE_LOG(LogTemp, Log, TEXT("Hell yeah level up: %d"), Level);
}