// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UI/Game/EnemyResourceBarWidget.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/WidgetComponent.h"

#include "EnemyHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDamageTaken);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnZeroHealth);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MORTALIS_API UEnemyHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UEnemyHealthComponent();

	UFUNCTION(BlueprintCallable)
	void TakeDamage(float Damage);

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UEnemyResourceBarWidget> HealthBarWidgetClass;

	// Delegates
	UPROPERTY(BLueprintCallable, BlueprintAssignable)
	FOnDamageTaken OnDamageTaken;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnZeroHealth OnZeroHealth;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UWidgetComponent* RootWidget;
	UEnemyResourceBarWidget* HealthBarWidget;

	float CurrentHealth;

	bool bIsAlive = true;
};
