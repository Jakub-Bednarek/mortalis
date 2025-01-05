// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/PlayerComponents/SpecialAttackComponent.h"

#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

USpecialAttackComponent::USpecialAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USpecialAttackComponent::BeginPlay()
{
	Super::BeginPlay();
	const auto ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	ViewportCenter = FVector(ViewportSize.X / 2.0f, ViewportSize.Y / 2.0f, 0.0f);
}

void USpecialAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USpecialAttackComponent::Execute(UPlayerStatisticsComponent* PlayerStatistics)
{
	if (not CanExecuteAttack(PlayerStatistics))
	{
		return;
	}

	ExecuteAttack(PlayerStatistics);
}

void USpecialAttackComponent::ExecuteAttack(UPlayerStatisticsComponent* PlayerStatistics) 
{
	const auto Direction = CalculateAttackDirection();
	// TODO: change hardcoded offset to var
	auto TargetLocation = GetOwner()->GetActorLocation() + (150.0f * Direction);
	auto* SpawnedProjectile = (ABasicProjectile*)GetWorld()->SpawnActor<AActor>(SpecialProjectile, TargetLocation, FRotator(0.0f));

	if (IsValid(SpawnedProjectile))
	{
		SpawnedProjectile->SetBaseDamage(PlayerStatistics->GetBaseNormalAttackDamage());
		SpawnedProjectile->Fire(Direction);
	}

	PlayerStatistics->ChangeCurrentMana(-AttackManaCost);
}

bool USpecialAttackComponent::CanExecuteAttack(const UPlayerStatisticsComponent* PlayerStatistics) const
{
	return PlayerStatistics->GetCurrentMana() >= AttackManaCost;
}

FVector USpecialAttackComponent::CalculateAttackDirection() const
{
	float MouseX;
	float MouseY;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(MouseX, MouseY);

	auto Direction = (ViewportCenter - FVector(MouseX, MouseY, 0.0f));
	Direction.Normalize();
	Direction = FVector(Direction.Y, -Direction.X, 0.0f); // Swap X and Y coordinates to align with world axis

	if (Direction.X == 0.0f and Direction.Y == 0.0f)
	{
		return FVector(0.5f, 0.5f, 0.0f);
	}

	return Direction;
}