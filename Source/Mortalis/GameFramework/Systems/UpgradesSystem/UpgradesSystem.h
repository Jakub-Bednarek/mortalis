// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Systems/ExperienceSystem.h"
#include "Upgrades/UpgradeBase.h"
#include "UI/Game/SUpgradeSelectionWidget.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UpgradesSystem.generated.h"

UCLASS()
class MORTALIS_API AUpgradesSystem : public AActor
{
	GENERATED_BODY()

public:	
	AUpgradesSystem();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void RegisterUpgrade();

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AExperienceSystem* ExperienceSystem;

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
	TArray<AUpgradeBase*> RegisteredUpgrades {};

	TArray<AUpgradeBase*> PlayerSelectedUpgrades {};
	TArray<AUpgradeBase*> UpgradesToBeSelected {};

	TSharedPtr<SUpgradeSelectionWidget> UpgradeSelectionWidget;
};
