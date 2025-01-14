// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatisticsHUD.h"
#include "GameFramework/Systems/ExperienceSystem.h"

#include "Components/ProgressBar.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

void UPlayerStatisticsHUD::InitializeBindings()
{
	TArray<AActor*> ExperienceSystemActors {};
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AExperienceSystem::StaticClass(), ExperienceSystemActors);
	if (ExperienceSystemActors.Num() != 1)
	{
		UE_LOG(LogTemp, Error, TEXT("Unexpected number of ExperienceSystem actors found in ArcherCharacter."));
	}
	else
	{
		AExperienceSystem* ExprienceSystem = (AExperienceSystem*)ExperienceSystemActors[0];
		ExprienceSystem->OnExperienceGainedEvent.AddDynamic(this, &UPlayerStatisticsHUD::SetExperience);
	}
}

void UPlayerStatisticsHUD::SetHealth(const float CurrentHealth, const float MaxHealth)
{
    if (HealthBar)
    {
        HealthBar->SetPercent(CurrentHealth / MaxHealth);
    }
}

void UPlayerStatisticsHUD::SetMana(const float CurrentMana, const float MaxMana)
{
    if (ManaBar)
    {
        ManaBar->SetPercent(CurrentMana / MaxMana);
    }
}

void UPlayerStatisticsHUD::SetExperience(const float CurrentExperience, const float MaxExperience)
{
    if (ExperienceBar)
    {
        ExperienceBar->SetPercent(CurrentExperience / MaxExperience);
    }
}