// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "UI/Game/PlayerStatisticsHUD.h"

#include "PlayerStatisticsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MORTALIS_API UPlayerStatisticsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerStatisticsComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ChangeCurrentHealth(float Delta);

	UFUNCTION(BlueprintCallable)
	void ChangeMaxHealth(float Delta);

	UFUNCTION(BlueprintCallable)
	void ChangeCurrentMana(float Delta);

	UFUNCTION(BlueprintCallable)
	void ChangeMaxMana(float Delta);

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UPlayerStatisticsHUD> PlayerStatisticsHUDClass;

private:
	TObjectPtr<UPlayerStatisticsHUD> PlayerStatisticsHUD;

	double MovementSpeed = 400.0;
	double AttacksPerSecond = 2.0;

	double MaxHealth = 100.0;
	double CurrentHealth = MaxHealth;
	double HealthRegenerationPerSecond = 0.2;

	double MaxMana = 50.0;
	double CurrentMana = MaxMana;
	double ManaRegenerationPerSecond = 10.0;
	double SpecialAttackManaCost = 50.0;
};
