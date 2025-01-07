// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradesSystem.h"

#include "Engine/GameViewportClient.h"
#include "Internationalization/Internationalization.h"
#include "Rendering/SlateRenderTransform.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

#include "GameFramework/Systems/UpgradesSystem/UpgradesSystem.h"

AUpgradesSystem::AUpgradesSystem()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AUpgradesSystem::BeginPlay()
{
	Super::BeginPlay();
	
	check(ExperienceSystem);

	ExperienceSystem->OnCharacterLevelUp.AddDynamic(this, &AUpgradesSystem::StartUpgradeProcedure);

	UpgradeSelectionWidget = SNew(SUpgradeSelectionWidget);
	UpgradeSelectionWidget->OnOptionSelectedEvent.AddUObject(this, &AUpgradesSystem::OnUpgradeSelected);

	Upgrade = NewObject<UUpgrade>(UUpgrade::StaticClass());
}

// Called every frame
void AUpgradesSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUpgradesSystem::RegisterUpgrade()
{

}

void AUpgradesSystem::StartUpgradeProcedure(const uint32)
{
	GenerateRandomUpgrades();
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	UpgradeSelectionWidget->ShowSelectionMenu(TArray<FText>{NSLOCTEXT("Upgrades", "Up1", "Upgrade1"), NSLOCTEXT("Upgrades", "Up2", "Upgrade2"), NSLOCTEXT("Upgrades", "Up3", "Upgrade3")});
}

void AUpgradesSystem::OnUpgradeSelected(const UpgradeChoice)
{
	UpgradeSelectionWidget->HideSelectionMenu();
	UGameplayStatics::SetGamePaused(GetWorld(), false);

	if (OnUpgradeGenerated.IsBound() and Upgrade != nullptr)
	{
		OnUpgradeGenerated.Broadcast(Upgrade);
	}
}

void AUpgradesSystem::GenerateRandomUpgrades()
{

}