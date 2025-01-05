// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyHealthComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "Engine/EngineTypes.h"

// Sets default values for this component's properties
UEnemyHealthComponent::UEnemyHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	RootWidget = CreateDefaultSubobject<UWidgetComponent>(FName(TEXT("Widget Component")));
}


// Called when the game starts
void UEnemyHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	RootWidget->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	RootWidget->SetWidgetClass(HealthBarWidgetClass);
	RootWidget->SetDrawAtDesiredSize(true);
	RootWidget->SetWidgetSpace(EWidgetSpace::Screen);
	RootWidget->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// TODO: Set Z offset based on model size instead of hardcode	
	RootWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));

	RootWidget->InitWidget();

	HealthBarWidget = Cast<UEnemyResourceBarWidget>(RootWidget->GetUserWidgetObject());
	HealthBarWidget->SetResourcePercentage(CurrentHealth, MaxHealth);
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

	HealthBarWidget->SetResourcePercentage(CurrentHealth, MaxHealth);
}

bool UEnemyHealthComponent::IsAlive() const
{
	return bIsAlive;
}