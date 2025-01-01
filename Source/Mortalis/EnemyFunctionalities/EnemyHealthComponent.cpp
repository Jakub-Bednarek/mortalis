// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyHealthComponent.h"

// Sets default values for this component's properties
UEnemyHealthComponent::UEnemyHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}


// Called every frame
void UEnemyHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UEnemyHealthComponent::TakeDamage(const float Damage)
{
	CurrentHealth -= Damage;

	if(OnDamageTaken.IsBound())
	{
		OnDamageTaken.Broadcast();
	}

	if (CurrentHealth <= 0.0f)
	{
		CurrentHealth = 0.0f;
		bIsAlive = false;

		if(OnDeath.IsBound())
		{
			OnDeath.Broadcast();
		}
	}
}

bool UEnemyHealthComponent::IsAlive() const
{
	return bIsAlive;
}