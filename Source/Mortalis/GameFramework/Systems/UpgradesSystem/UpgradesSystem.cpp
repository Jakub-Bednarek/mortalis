// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/Systems/UpgradesSystem/UpgradesSystem.h"
#include "Components/SlateWrapperTypes.h"
#include "CoreGlobals.h"
#include "GameFramework/Types/PoolIndex.h"
#include "GameFramework/Types/UpgradeCategory.h"
#include "Internationalization/Internationalization.h"
#include "Logging/LogMacros.h"
#include "Logging/LogVerbosity.h"
#include "Upgrades/NormalAttackComponentUpgrade.h"
#include "Upgrades/SkillComponentUpgrade.h"
#include "Upgrades/SpecialAttackComponentUpgrade.h"
#include "Upgrades/StatisticsComponentUpgrade.h"
#include "Upgrades/UpgradeUIData.h"

#include "Upgrades/HealthUpgrade.h"
#include "Upgrades/FireballSkillUpgrade.h"
#include "Upgrades/NormalAttackDamageUpgrade.h"
#include "Upgrades/SpecialAttackDamageUpgrade.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

AUpgradesSystem::AUpgradesSystem()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AUpgradesSystem::BeginPlay()
{
	Super::BeginPlay();
	
	RegisterTestUpgrades();

	if (not ExperienceSystem)
	{
		UE_LOG(LogTemp, Error, TEXT("ExperienceSystem actor is not set in UpgradesSystem"));
	}
	else
	{
		ExperienceSystem->OnCharacterLevelUp.AddDynamic(this, &AUpgradesSystem::StartUpgradeProcedure);
	}
	
	UpgradeCategoryEntriesCount = (StaticEnum<EUpgradeCategory>()->GetMaxEnumValue() - 1);

	if (not UpgradeSelectionWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("Upgrade Selection Widget class is not set."));
	}
	else
	{
		UpgradeSelectionWidget = (UUpgradeSelectionWidget*)(CreateWidget(UGameplayStatics::GetPlayerController(GetWorld(), 0), UpgradeSelectionWidgetClass));
		UpgradeSelectionWidget->AddToPlayerScreen();
		UpgradeSelectionWidget->HideSelectionMenu();
		UpgradeSelectionWidget->InitializeBindings();
		UpgradeSelectionWidget->OnOptionSelectedEvent.BindDynamic(this, &AUpgradesSystem::FinishUpgradeProcedure);
	}
}

void AUpgradesSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

TArray<FUpgradeUIData> AUpgradesSystem::GenerateUpgradeChoices(const uint8 Count, const TArray<EUpgradeCategory>& ActiveUpgradePools)
{
	TArray<FUpgradeUIData> GeneratedUpgrades {};

	for (auto i = 0; i < DefaultNumberOfUpgradesToGenerate; i++)
	{
		auto CategoryToSelect = GetRandomUpgradeCategory(ActiveUpgradePools);

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

EUpgradeCategory AUpgradesSystem::GetRandomUpgradeCategory(const TArray<EUpgradeCategory>& ActiveUpgradesPools) const
{
	static int32 UpgradeCategoryLowerBound = 0;

	return ActiveUpgradesPools[FMath::RandRange(UpgradeCategoryLowerBound, ActiveUpgradesPools.Num() - 1)];
}

TArray<EUpgradeCategory> AUpgradesSystem::GetActiveUpgradePools() const
{
	TArray<EUpgradeCategory> ActivePools {};

	if (not StatisticsUpgradesPool.IsExhausted())
	{
		ActivePools.Push(EUpgradeCategory::Statistics);
	}
	if (not NormalAttackUpgradesPool.IsExhausted())
	{
		ActivePools.Push(EUpgradeCategory::NormalAttack);
	}
	if (not SpecialAttackUpgradesPool.IsExhausted())
	{
		ActivePools.Push(EUpgradeCategory::SpecialAttack);
	}
	if (not SkillsUpgradesPool.IsExhausted())
	{
		ActivePools.Push(EUpgradeCategory::Skill);
	}

	return ActivePools;
}

void AUpgradesSystem::StartUpgradeProcedure(uint32 Level)
{
	UE_LOG(LogTemp, Verbose, TEXT("Starting upgrade procedure for level %d."), Level);
	
	const auto ActiveUpgradesPools = GetActiveUpgradePools();
	if (ActiveUpgradesPools.Num() == 0)
	{
		UE_LOG(LogTemp, Verbose, TEXT("All upgrades pools exhausted, not proceeding with upgrade sequence."));
		return;
	}

	auto GeneratedUpgradeChoicesData = GenerateUpgradeChoices(DefaultNumberOfUpgradesToGenerate, ActiveUpgradesPools);
	if (OnUpgradeProcedureBegin.IsBound())
	{
		OnUpgradeProcedureBegin.Broadcast(GeneratedUpgradeChoicesData);
	}

	UpgradeSelectionWidget->ShowSelectionMenu(GeneratedUpgradeChoicesData);

	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void AUpgradesSystem::FinishUpgradeProcedure(const FUpgradeIndex Index, const EUpgradeCategory Category)
{
	UE_LOG(LogTemp, Verbose, TEXT("Finishing upgrade procedure."));

	MarkAndPropagateSelectedUpgrade(Index, Category);
	UpgradeSelectionWidget->HideSelectionMenu();

	if (OnUpgradeProcedureEnd.IsBound())
	{
		OnUpgradeProcedureEnd.Broadcast();
	}

	UGameplayStatics::SetGamePaused(GetWorld(), false);
}

void AUpgradesSystem::MarkAndPropagateSelectedUpgrade(FUpgradeIndex Index, EUpgradeCategory Category)
{
	switch (Category)
	{
		case EUpgradeCategory::Statistics:
		{
			auto* UpgradeInstance = StatisticsUpgradesPool.SelecteNextUpgrade(Index);
			if (UpgradeInstance != nullptr and OnStatisticsComponentUpgradeSelected.IsBound())
			{
				OnStatisticsComponentUpgradeSelected.Broadcast(UpgradeInstance);
			}
			break;
		}
		case EUpgradeCategory::NormalAttack:
		{
			auto* UpgradeInstance = NormalAttackUpgradesPool.SelecteNextUpgrade(Index);
			if (UpgradeInstance != nullptr and OnNormalAtatckComponentUpgradeSelected.IsBound())
			{
				OnNormalAtatckComponentUpgradeSelected.Broadcast(UpgradeInstance);
			}
			break;
		}
		case EUpgradeCategory::SpecialAttack:
		{
			auto* UpgradeInstance = SpecialAttackUpgradesPool.SelecteNextUpgrade(Index);
			if (UpgradeInstance != nullptr and OnSpecialAttackComponentUpgradeSelected.IsBound())
			{
				OnSpecialAttackComponentUpgradeSelected.Broadcast(UpgradeInstance);
			}
			break;
		}
		case EUpgradeCategory::Skill:
		{
			auto* UpgradeInstance = SkillsUpgradesPool.SelecteNextUpgrade(Index);
			if (UpgradeInstance != nullptr and OnSkillUpgradeSelected.IsBound())
			{
				OnSkillUpgradeSelected.Broadcast(UpgradeInstance);
			}
			break;
		}
		default:
			UE_LOG(LogTemp, Error, TEXT("Can't propagate selected upgrade, category is currently not handled: %d"), static_cast<uint8>(Category));
			break;
	}
}

void AUpgradesSystem::RegisterTestUpgrades()
{
	auto HealthUpgradeChain = StatisticsUpgradesPool.CreateChain();
	auto* HealthUpgrade1 = 
		UpgradeFactory::Create<UHealthUpgrade>()
		.WithName(FName(TEXT("Health Upgrade 1")))
		.WithDescription(FName(TEXT("Test description")))
		.Build();

	HealthUpgradeChain.RegisterUpgrade(HealthUpgrade1);
	StatisticsUpgradesPool.RegisterChain({0}, MoveTemp(HealthUpgradeChain));
}