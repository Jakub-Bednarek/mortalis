// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatisticsComponent.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

UPlayerStatisticsComponent::UPlayerStatisticsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerStatisticsComponent::BeginPlay()
{
	Super::BeginPlay();

	check(PlayerStatisticsHUDClass);

	PlayerStatisticsHUD = (UPlayerStatisticsHUD*)(CreateWidget(UGameplayStatics::GetPlayerController(GetWorld(), 0), PlayerStatisticsHUDClass));
	PlayerStatisticsHUD->AddToPlayerScreen();

	PlayerStatisticsHUD->SetHealth(CurrentHealth, MaxHealth);
	PlayerStatisticsHUD->SetMana(CurrentMana, MaxMana);
}

void UPlayerStatisticsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPlayerStatisticsComponent::ChangeCurrentHealth(const float Delta)
{
	CurrentHealth += Delta;
	PlayerStatisticsHUD->SetHealth(CurrentHealth, MaxHealth);
}

void UPlayerStatisticsComponent::ChangeMaxHealth(const float Delta)
{
	MaxHealth += Delta;
	PlayerStatisticsHUD->SetHealth(CurrentHealth, MaxHealth);
}

void UPlayerStatisticsComponent::ChangeCurrentMana(const float Delta)
{
	CurrentMana += Delta;
	PlayerStatisticsHUD->SetMana(CurrentMana, MaxMana);
}

void UPlayerStatisticsComponent::ChangeMaxMana(const float Delta)
{
	MaxMana += Delta;
	PlayerStatisticsHUD->SetMana(CurrentMana, MaxMana);
}

float UPlayerStatisticsComponent::GetAttacksPerSecond() const
{
	return AttacksPerSecond;
}

float UPlayerStatisticsComponent::GetBaseNormalAttackDamage() const
{
	return BaseNormalAttackDamage;
}