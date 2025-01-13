// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UpgradesPool.h"

#include "Upgrades/StatisticsComponentUpgrade.h"
#include "Upgrades/NormalAttackComponentUpgrade.h"
#include "Upgrades/SpecialAttackComponentUpgrade.h"
#include "Upgrades/SkillComponentUpgrade.h"

#include "GameFramework/Systems/ExperienceSystem.h"
#include "GameFramework/Types/UpgradeCategory.h"

#include "UI/Game/UpgradeSelectionWidget.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UpgradesSystem.generated.h"

// Whole upgrade procedure is gonna be like a fucking ping pong of events, not a fan of that
// We're exchanging (most likely) a performance for low coupling :/

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpgradeProcedureBegin, const TArray<FUpgradeUIData>&, RandomUpgradesUIData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpgradeProcedureEnd);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatisticsComponentUpgradeSelected, UStatisticsComponentUpgrade*, Upgrade);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNormalAtatckComponentUpgradeSelected, UNormalAttackComponentUpgrade*, Upgrade);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpecialAttackComponentUpgradeSelected, USpecialAttackComponentUpgrade*, Upgrade);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSkillUpgradeSelected, USkillComponentUpgrade*, Upgrade);

UCLASS()
class MORTALIS_API AUpgradesSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	AUpgradesSystem();

	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere)
	AExperienceSystem* ExperienceSystem;

	UPROPERTY()
	FOnUpgradeProcedureBegin OnUpgradeProcedureBegin;
	
	UPROPERTY()
	FOnUpgradeProcedureEnd OnUpgradeProcedureEnd;

	UPROPERTY()
	FOnStatisticsComponentUpgradeSelected OnStatisticsComponentUpgradeSelected;

	UPROPERTY()
	FOnNormalAtatckComponentUpgradeSelected OnNormalAtatckComponentUpgradeSelected;

	UPROPERTY()
	FOnSpecialAttackComponentUpgradeSelected OnSpecialAttackComponentUpgradeSelected;

	UPROPERTY()
	FOnSkillUpgradeSelected OnSkillUpgradeSelected;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUpgradeSelectionWidget> UpgradeSelectionWidgetClass;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void StartUpgradeProcedure(uint32 Level);

	UFUNCTION()
	void FinishUpgradeProcedure(FUpgradeIndex Index, EUpgradeCategory Category);

	TArray<FUpgradeUIData> GenerateUpgradeChoices(uint8 Count);

	EUpgradeCategory GetRandomUpgradeCategory() const;

	void RegisterTestUpgrades();

	void MarkAndPropagateSelectedUpgrade(FUpgradeIndex Index, EUpgradeCategory Category);

private:
	static constexpr uint8 DefaultNumberOfUpgradesToGenerate = 3;

	int64 UpgradeCategoryEntriesCount = 0;

	UUpgradeSelectionWidget* UpgradeSelectionWidget;

	UpgradesPool<UStatisticsComponentUpgrade*> StatisticsUpgradesPool;
	UpgradesPool<UNormalAttackComponentUpgrade*> NormalAttackUpgradesPool;
	UpgradesPool<USpecialAttackComponentUpgrade*> SpecialAttackUpgradesPool;
	UpgradesPool<USkillComponentUpgrade*> SkillsUpgradesPool;
};
