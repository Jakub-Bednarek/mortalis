// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "GameFramework/Systems/ExperienceSystem.h"
#include "GameFramework/PlayerComponents/PlayerStatisticsComponent.h"
#include "GameFramework/PlayerComponents/NormalAttackComponent.h"
#include "Upgrades/UpgradeBase.h"
#include "UI/Game/SUpgradeSelectionWidget.h"

#include "UpgradesSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpgradeGenerated, UUpgrade*, GeneratedUpgrade);

class UBaseUpgradeApplier
{
public:
	using TargetType = UPlayerStatisticsComponent;

	virtual void operator()(UPlayerStatisticsComponent* Target) {}
};

class UNormalAttackUpgradeApplier
{
public:
	using TargetType = UNormalAttackComponent;

	void operator()(UNormalAttackComponent* Target) {}
};

// class USpecialAttackUpgradeApplier
// {
// public:
// 	virtual void operator()(USpecialAttackUpgradeApplier* Target) {}
// };

// UCLASS()
// class USkillUpgradeApplier : public UUpgradeBase
// {
// 	GENERATED_BODY()

// public:
// 	USkillUpgradeApplier()
// 	{
// 		UUpgradeBase::Register<USkillUpgradeApplier>();
// 	}

// 	virtual void operator()(UNormalAttackComponent* Target) {}
// };

UCLASS()
class MORTALIS_API AUpgradesSystem : public AActor
{
	GENERATED_BODY()

public:	
	AUpgradesSystem();

	virtual void Tick(float DeltaTime) override;

	void RegisterUpgrade();

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AExperienceSystem* ExperienceSystem;

	UPROPERTY()
	FOnUpgradeGenerated OnUpgradeGenerated;
protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void StartUpgradeProcedure(uint32 Level);

	UFUNCTION()
	void OnUpgradeSelected(const UpgradeChoice Choice);

	UFUNCTION()
	void GenerateRandomUpgrades();
private:
	UUpgradeAppliers<UBaseUpgradeApplier, UNormalAttackUpgradeApplier> UpgradeAppliers;
	// TArray<UUpgrade*> RegisteredUpgrades {};

	// TArray<UUpgrade*> PlayerSelectedUpgrades {};
	// TArray<UUpgrade*> UpgradesToBeSelected {};

	TSharedPtr<SUpgradeSelectionWidget> UpgradeSelectionWidget;
	UUpgrade* Upgrade = nullptr;
};
