// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/Systems/UpgradesSystem/UpgradesSystem.h"
#include "Components/SlateWrapperTypes.h"
#include "CoreGlobals.h"
#include "GameFramework/Types/PoolIndex.h"
#include "GameFramework/Types/UpgradeCategory.h"
#include "Internationalization/Internationalization.h"
#include "Logging/LogMacros.h"
#include "Logging/LogVerbosity.h"

#include "Templates/UnrealTemplate.h"
#include "Upgrades/NormalAttackComponentUpgrade.h"
#include "Upgrades/SkillComponentUpgrade.h"
#include "Upgrades/SpecialAttackComponentUpgrade.h"
#include "Upgrades/StatisticsComponentUpgrade.h"
#include "Upgrades/UpgradeUIData.h"

#include "Upgrades/StatisticsUpgrades.h"
#include "Upgrades/SkillUpgrades.h"
#include "Upgrades/NormalAttackUpgrades.h"
#include "Upgrades/SpecialAttackUpgrades.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

AUpgradesSystem::AUpgradesSystem()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AUpgradesSystem::BeginPlay()
{
	Super::BeginPlay();
	
	RegisterUpgrades();

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

void AUpgradesSystem::RegisterStatisticsUpgrades()
{
	auto HealthUpgradeChain = StatisticsUpgradesPool.CreateChain();
	auto* HealthUpgrade1 = 
		UpgradeFactory::Create<UStatisticsHealthUpgrade>()
		.WithName(FName(TEXT("Health Upgrade 1")))
		.WithDescription(FName(TEXT("Adds 5 maximum health")))
		.WithHealthValue(5)
		.Build();
	
	auto* HealthUpgrade2 = 
		UpgradeFactory::Create<UStatisticsHealthUpgrade>()
		.WithName(FName(TEXT("Health Upgrade 2")))
		.WithDescription(FName(TEXT("Adds 6 maximum health")))
		.WithHealthValue(6)
		.Build();
		
	auto* HealthUpgrade3 = 
		UpgradeFactory::Create<UStatisticsHealthUpgrade>()
		.WithName(FName(TEXT("Health Upgrade 3")))
		.WithDescription(FName(TEXT("Adds 7 maximum health")))
		.WithHealthValue(7)
		.Build();

	auto* HealthUpgrade4 = 
		UpgradeFactory::Create<UStatisticsHealthUpgrade>()
		.WithName(FName(TEXT("Health Upgrade 4")))
		.WithDescription(FName(TEXT("Adds 8 maximum health")))
		.WithHealthValue(8)
		.Build();
		
	auto* HealthUpgrade5 = 
		UpgradeFactory::Create<UStatisticsHealthUpgrade>()
		.WithName(FName(TEXT("Health Upgrade 5")))
		.WithDescription(FName(TEXT("Adds 10 maximum health")))
		.WithHealthValue(10)
		.Build();

	HealthUpgradeChain.RegisterUpgrade(HealthUpgrade1);
	HealthUpgradeChain.RegisterUpgrade(HealthUpgrade2);
	HealthUpgradeChain.RegisterUpgrade(HealthUpgrade3);
	HealthUpgradeChain.RegisterUpgrade(HealthUpgrade4);
	HealthUpgradeChain.RegisterUpgrade(HealthUpgrade5);
	StatisticsUpgradesPool.RegisterChain(MoveTemp(HealthUpgradeChain));

	auto DamageUpgradeChain = StatisticsUpgradesPool.CreateChain();
	auto* DamageUpgrade1 =
		UpgradeFactory::Create<UStatisticsDamageUpgrade>()
		.WithName(FName(TEXT("Damage Upgrade 1")))
		.WithDescription(FName(TEXT("Increases damage by 10")))
		.WithDamageValue(10.0f)
		.Build();
	
	auto* DamageUpgrade2 =
		UpgradeFactory::Create<UStatisticsDamageUpgrade>()
		.WithName(FName(TEXT("Damage Upgrade 2")))
		.WithDescription(FName(TEXT("Increases damage by 15")))
		.WithDamageValue(15.0f)
		.Build();
		
	auto* DamageUpgrade3 =
		UpgradeFactory::Create<UStatisticsDamageUpgrade>()
		.WithName(FName(TEXT("Damage Upgrade 3")))
		.WithDescription(FName(TEXT("Increases damage by 20")))
		.WithDamageValue(20.0f)
		.Build();
		
	auto* DamageUpgrade4 =
		UpgradeFactory::Create<UStatisticsDamageUpgrade>()
		.WithName(FName(TEXT("Damage Upgrade 4")))
		.WithDescription(FName(TEXT("Increases damage by 25")))
		.WithDamageValue(25.0f)
		.Build();
		
	auto* DamageUpgrade5 =
		UpgradeFactory::Create<UStatisticsDamageUpgrade>()
		.WithName(FName(TEXT("Damage Upgrade 5")))
		.WithDescription(FName(TEXT("Increases damage by 30")))
		.WithDamageValue(30.0f)
		.Build();
	
	DamageUpgradeChain.RegisterUpgrade(DamageUpgrade1);
	DamageUpgradeChain.RegisterUpgrade(DamageUpgrade2);
	DamageUpgradeChain.RegisterUpgrade(DamageUpgrade3);
	DamageUpgradeChain.RegisterUpgrade(DamageUpgrade4);
	DamageUpgradeChain.RegisterUpgrade(DamageUpgrade5);
	StatisticsUpgradesPool.RegisterChain(MoveTemp(DamageUpgradeChain));

	auto MovementSpeedUpgradeChain = StatisticsUpgradesPool.CreateChain();
	auto* MovementSpeedUpgrade1 =
		UpgradeFactory::Create<UStatisticsMovementSpeedUpgrade>()
		.WithName(FName(TEXT("Movement Speed Upgrade 1")))
		.WithDescription(FName(TEXT("Increases movement speed by 30")))
		.WithMovementSpeedValue(30.0f)
		.Build();
		
	auto* MovementSpeedUpgrade2 =
		UpgradeFactory::Create<UStatisticsMovementSpeedUpgrade>()
		.WithName(FName(TEXT("Movement Speed Upgrade 2")))
		.WithDescription(FName(TEXT("Increases movement speed by 40")))
		.WithMovementSpeedValue(40.0f)
		.Build();
		
	auto* MovementSpeedUpgrade3 =
		UpgradeFactory::Create<UStatisticsMovementSpeedUpgrade>()
		.WithName(FName(TEXT("Movement Speed Upgrade 3")))
		.WithDescription(FName(TEXT("Increases movement speed by 50")))
		.WithMovementSpeedValue(50.0f)
		.Build();
	
	MovementSpeedUpgradeChain.RegisterUpgrade(MovementSpeedUpgrade1);
	MovementSpeedUpgradeChain.RegisterUpgrade(MovementSpeedUpgrade2);
	MovementSpeedUpgradeChain.RegisterUpgrade(MovementSpeedUpgrade3);
	StatisticsUpgradesPool.RegisterChain(MoveTemp(MovementSpeedUpgradeChain));
	
	auto RegenerationUpgradeChain = StatisticsUpgradesPool.CreateChain();
	auto* RegenerationUpgrade1 =
		UpgradeFactory::Create<UStatisticsRegenerationUpgrade>()
		.WithName(FName(TEXT("Regeneration Upgrade 1")))
		.WithDescription(FName(TEXT("Increases Health Regeneration by 0.2\nIncrease Mana Regeneration by 5.0")))
		.WithHealthRegenerationValue(0.2f)
		.WithManaRegenerationValue(5.0f)
		.Build();
		
	auto* RegenerationUpgrade2 =
		UpgradeFactory::Create<UStatisticsRegenerationUpgrade>()
		.WithName(FName(TEXT("Regeneration Upgrade 2")))
		.WithDescription(FName(TEXT("Increases Health Regeneration by 0.35\nIncrease Mana Regeneration by 7.5")))
		.WithHealthRegenerationValue(0.35f)
		.WithManaRegenerationValue(7.5f)
		.Build();
		
	auto* RegenerationUpgrade3 =
		UpgradeFactory::Create<UStatisticsRegenerationUpgrade>()
		.WithName(FName(TEXT("Regeneration Upgrade 3")))
		.WithDescription(FName(TEXT("Increases Health Regeneration by 0.5\nIncrease Mana Regeneration by 10.0")))
		.WithHealthRegenerationValue(0.5f)
		.WithManaRegenerationValue(10.0f)
		.Build();
	
	RegenerationUpgradeChain.RegisterUpgrade(RegenerationUpgrade1);
	RegenerationUpgradeChain.RegisterUpgrade(RegenerationUpgrade2);
	RegenerationUpgradeChain.RegisterUpgrade(RegenerationUpgrade3);
	StatisticsUpgradesPool.RegisterChain(MoveTemp(MovementSpeedUpgradeChain));
}

void AUpgradesSystem::RegisterNormalAttackUpgrades()
{
	
}

void AUpgradesSystem::RegisterSpecialAttackUpgrades()
{
	
}

void AUpgradesSystem::RegisterSkillUpgrades()
{
	
}

void AUpgradesSystem::RegisterUpgrades()
{
	RegisterStatisticsUpgrades();
	RegisterNormalAttackUpgrades();
	RegisterSpecialAttackUpgrades();
	RegisterSkillUpgrades();
}