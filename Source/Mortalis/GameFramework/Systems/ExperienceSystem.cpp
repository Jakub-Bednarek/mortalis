// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/Systems/ExperienceSystem.h"

// Sets default values
AExperienceSystem::AExperienceSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AExperienceSystem::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AExperienceSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AExperienceSystem::AddExperience(const int32 Experience)
{
	if (Experience < 0.0f)
	{
		UE_LOG(LogTemp, Error, TEXT("AddExperience(): Experience must be greater than 0.0"));
		return;
	}

	CurrentExperience += Experience;
	if(CanLevelUp())
	{
		LevelUp();
	}
}

bool AExperienceSystem::CanLevelUp() const
{
	return CurrentExperience >= ExperienceForNextLevel;
}

void AExperienceSystem::LevelUp()
{
	CurrentExperience -= ExperienceForNextLevel;
	ExperienceForNextLevel *= 1.15f;
	++CurrentLevel;

	if (OnCharacterLevelUp.IsBound())
	{
		OnCharacterLevelUp.Broadcast(CurrentLevel);
	}
}