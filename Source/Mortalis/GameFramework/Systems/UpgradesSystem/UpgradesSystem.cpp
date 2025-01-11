// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/Systems/UpgradesSystem/UpgradesSystem.h"
#include "GameFramework/Types/UpgradeCategory.h"
#include "Upgrades/HealthUpgrade.h"
#include "Upgrades/UpgradeUIData.h"

AUpgradesSystem::AUpgradesSystem()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AUpgradesSystem::BeginPlay()
{
	Super::BeginPlay();
	
	RegisterHealthUpgradeChain();

	if (not ExperienceSystem)
	{
		UE_LOG(LogTemp, Error, TEXT("ExperienceSystem actor not set in UpgradesSystem"));
	}
	else
	{
		ExperienceSystem->OnCharacterLevelUp.AddDynamic(this, &AUpgradesSystem::StartUpgradeProcedure);
	}
	
	UpgradeCategoryEntriesCount = (StaticEnum<EUpgradeCategory>()->GetMaxEnumValue() - 1);
}

void AUpgradesSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<FUpgradeUIData> AUpgradesSystem::GenerateUpgradeChoices(const uint8 Count)
{
	TArray<FUpgradeUIData> GeneratedUpgrades {};

	for (auto i = 0; i < DefaultNumberOfUpgradesToGenerate; i++)
	{
		auto CategoryToSelect = GetRandomUpgradeCategory();

		switch (CategoryToSelect)
		{
			case EUpgradeCategory::Statistics:
				GeneratedUpgrades.Add(StatisticsUpgradesPool.GetUIDataFromRandomlySelected());
				break;
			case EUpgradeCategory::NormalAttack:
				GeneratedUpgrades.Add(NormalAttackUpgradesPool.GetUIDataFromRandomlySelected());
				break;
			case EUpgradeCategory::SpecialAttack:
				GeneratedUpgrades.Add(SpecialAttackUpgradesPool.GetUIDataFromRandomlySelected());
				break;
			case EUpgradeCategory::Skill:
				GeneratedUpgrades.Add(SkillsUpgradesPool.GetUIDataFromRandomlySelected());
				break;
			default:
				UE_LOG(LogTemp, Error, TEXT("Unknown category selected for skill upgrade: %d"), CategoryToSelect);
				break;
		}
	}

	return GeneratedUpgrades;
}

EUpgradeCategory AUpgradesSystem::GetRandomUpgradeCategory() const
{
	static int64 UpgradeCategoryLowerBound = 0;

	return static_cast<EUpgradeCategory>(FMath::RandRange(UpgradeCategoryLowerBound, UpgradeCategoryEntriesCount));
}

void AUpgradesSystem::StartUpgradeProcedure(uint32 Level)
{
	UE_LOG(LogTemp, Verbose, TEXT("Starting upgrade for level %d"), Level);

	auto GeneratedUpgradeChoicesData = GenerateUpgradeChoices(DefaultNumberOfUpgradesToGenerate);

	if (OnUpgradeProcedureBegin.IsBound())
	{
		OnUpgradeProcedureBegin.Broadcast(GeneratedUpgradeChoicesData);
	}
}

void AUpgradesSystem::FinishUpgradeProcedure()
{
	if (OnUpgradeProcedureEnd.IsBound())
	{
		OnUpgradeProcedureEnd.Broadcast();
	}
}

void AUpgradesSystem::RegisterHealthUpgradeChain()
{
	auto Upgrade = UpgradeFactory::Create<UHealthUpgrade>();
}