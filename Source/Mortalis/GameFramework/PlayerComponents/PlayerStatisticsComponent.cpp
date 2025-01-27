// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatisticsComponent.h"
#include "GameManager.h"

#include "Engine/Player.h"
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
	PlayerStatisticsHUD->InitializeBindings();
}

void UPlayerStatisticsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ApplyRegenerations(DeltaTime);
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

void UPlayerStatisticsComponent::TakeDamage(const float Damage)
{
	if (Damage < 0.0)
	{
		UE_LOG(LogTemp, Error, TEXT("TakeDamage(): Damage must be greater or equal 0."));
		return;
	}

	CurrentHealth -= Damage;
	PlayerStatisticsHUD->SetHealth(CurrentHealth, MaxHealth);

	if (CurrentHealth <= 0.0)
	{
		if (OutOfHealthEvent.IsBound())
		{
			OutOfHealthEvent.Broadcast();
		}
	}
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


void UPlayerStatisticsComponent::IncreaseDamage(float Delta)
{
	BaseNormalAttackDamage += Delta;
}

void UPlayerStatisticsComponent::IncreaseAttackSpeed(float Delta)
{
	AttacksPerSecond += Delta;
}

void UPlayerStatisticsComponent::IncreaseMovementSpeed(float Delta)
{
	MovementSpeed += Delta;
}

void UPlayerStatisticsComponent::IncreaseHealthRegeneration(float Delta)
{
	HealthRegenerationPerSecond += Delta;
}

void UPlayerStatisticsComponent::IncreaseManaRegeneration(float Delta)
{
	ManaRegenerationPerSecond += Delta;
}

float UPlayerStatisticsComponent::GetAttacksPerSecond() const
{
	return AttacksPerSecond;
}

float UPlayerStatisticsComponent::GetCurrentHealth() const
{
	return CurrentHealth;
}

float UPlayerStatisticsComponent::GetCurrentMana() const
{
	return CurrentMana;
}

float UPlayerStatisticsComponent::GetBaseNormalAttackDamage() const
{
	return BaseNormalAttackDamage;
}

float UPlayerStatisticsComponent::GetMovementSpeed() const
{
	return MovementSpeed;
}

void UPlayerStatisticsComponent::ApplyRegenerations(const float DeltaTime)
{
	if (CurrentHealth < MaxHealth)
	{
		const auto HealthToAdd = HealthRegenerationPerSecond * DeltaTime;

		CurrentHealth = (CurrentHealth + HealthToAdd) > MaxHealth
							? MaxHealth 
							: CurrentHealth + HealthToAdd;
	}

	if (CurrentMana < MaxMana)
	{
		const auto ManaToAdd = ManaRegenerationPerSecond * DeltaTime;

		CurrentMana = (CurrentMana + ManaToAdd) > MaxMana
							? MaxMana
							: CurrentMana + ManaToAdd;
	}

	// TODO: way too fucking often
	PlayerStatisticsHUD->SetHealth(CurrentHealth, MaxHealth);
	PlayerStatisticsHUD->SetMana(CurrentMana, MaxMana);
}