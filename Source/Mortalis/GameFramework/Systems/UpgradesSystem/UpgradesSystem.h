// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UpgradesPool.h"

#include "Upgrades/StatisticsComponentUpgrade.h"
#include "Upgrades/NormalAttackComponentUpgrade.h"
#include "Upgrades/SpecialAttackComponentUpgrade.h"
#include "Upgrades/SkillComponentUpgrade.h"

#include "GameFramework/Systems/ExperienceSystem.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UpgradesSystem.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnUpgradeProcedureBegin);
DECLARE_DYNAMIC_DELEGATE(FOnUpgradeProcedureEnd);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatisticsComponentUpgradeSelected, UStatisticsComponentUpgrade*, Upgrade);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNormalAtatckComponentUpgradeSelected, UStatisticsComponentUpgrade*, Upgrade);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpecialAttackComponentUpgradeSelected, UStatisticsComponentUpgrade*, Upgrade);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSkillUpgradeSelected, UStatisticsComponentUpgrade*, Upgrade);

UCLASS()
class MORTALIS_API AUpgradesSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	AUpgradesSystem();

	virtual void Tick(float DeltaTime) override;
public:
	UPROPERTY()
	AExperienceSystem* ExperienceSystem;

protected:
	virtual void BeginPlay() override;

private:
	UpgradesPool<UStatisticsComponentUpgrade> StatisticsUpgradesPool;
	UpgradesPool<UNormalAttackComponentUpgrade> NormalAttackUpgradesPool;
	UpgradesPool<USpecialAttackComponentUpgrade> SpecialAttackUpgradesPool;
	UpgradesPool<USkillComponentUpgrade> SkillsUpgradesPool;
};
