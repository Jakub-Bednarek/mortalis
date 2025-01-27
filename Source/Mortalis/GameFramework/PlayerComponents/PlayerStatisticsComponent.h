// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "UI/Game/PlayerStatisticsHUD.h"

#include "PlayerStatisticsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOutOfHealthEvent);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MORTALIS_API UPlayerStatisticsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerStatisticsComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ChangeCurrentHealth(float Delta);

	UFUNCTION(BlueprintCallable)
	void ChangeMaxHealth(float Delta);

	UFUNCTION(BlueprintCallable)
	void ChangeCurrentMana(float Delta);

	UFUNCTION(BlueprintCallable)
	void IncreaseDamage(float Delta);

	UFUNCTION(BlueprintCallable)
	void IncreaseAttackSpeed(float Delta);

	UFUNCTION(BlueprintCallable)
	void IncreaseMovementSpeed(float Delta);

	UFUNCTION(BlueprintCallable)
	void IncreaseHealthRegeneration(float Delta);

	UFUNCTION(BlueprintCallable)
	void IncreaseManaRegeneration(float Delta);

	UFUNCTION(BlueprintCallable)
	void TakeDamage(float Damage);

	UFUNCTION(BlueprintCallable)
	void ChangeMaxMana(float Delta);
	
	UFUNCTION(BlueprintCallable)
	float GetCurrentHealth() const;
	
	UFUNCTION(BlueprintCallable)
	float GetCurrentMana() const;

	UFUNCTION(BlueprintCallable)
	float GetAttacksPerSecond() const;

	UFUNCTION(BlueprintCallable)
	float GetMovementSpeed() const;

	UFUNCTION(BlueprintCallable)
	float GetBaseNormalAttackDamage() const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UPlayerStatisticsHUD> PlayerStatisticsHUDClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FOutOfHealthEvent OutOfHealthEvent;

protected:
	virtual void BeginPlay() override;

private:
	void ApplyRegenerations(float DeltaTime);

private:
	TObjectPtr<UPlayerStatisticsHUD> PlayerStatisticsHUD;

	double MovementSpeed = 400.0;
	double AttacksPerSecond = 1.0;

	float BaseNormalAttackDamage = 25.0f;

	double MaxHealth = 100.0;
	double CurrentHealth = MaxHealth;
	double HealthRegenerationPerSecond = 0.2;

	double MaxMana = 50.0;
	double CurrentMana = MaxMana;
	double ManaRegenerationPerSecond = 10.0;
	double SpecialAttackManaCost = 50.0;
};
