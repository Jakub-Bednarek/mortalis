// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/Systems/UpgradesSystem/UpgradesSystem.h"
#include "Upgrades/HealthUpgrade.h"

// Sets default values
AUpgradesSystem::AUpgradesSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUpgradesSystem::BeginPlay()
{
	Super::BeginPlay();
	
	RegisterHealthUpgradeChain();
}

// Called every frame
void AUpgradesSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUpgradesSystem::RegisterHealthUpgradeChain()
{
	auto Upgrade = UpgradeFactory::Create<UHealthUpgrade>();
}